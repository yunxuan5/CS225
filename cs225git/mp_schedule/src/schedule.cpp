/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <deque>

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text("filename");

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    std::ifstream file(filename);
    if(!file.is_open()){
      return V2D();
    }
    std::vector<std::vector<std::string>> result;
    std::string line;
    while(std::getline(file, line)){
      std::vector<std::string> word;
      SplitString(line, ',', word);
      std::vector<std::string> row;
      for(unsigned i = 0; i < word.size(); i++){
        row.push_back(Trim(word[i]));
      }
      result.push_back(row);
    }
  return result;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
    // YOUR CODE HERE
    V2D Correct_Roster;
    for(unsigned i = 0; i < cv.size(); i++){
      std::vector<std::string> line = cv[i];
      std::string course = line[0];
      std::string stu;
      bool rightcourse = false;
      std::vector<std::string> right_stu;
      for(unsigned j = 1; j < line.size(); j++){
        stu = line[j];
        for(unsigned k = 0; k < student.size(); k++){
          if(student[k][0] == stu){
            for (unsigned l = 1; l < student[k].size(); l++){
              if(student[k][l] == course){
                rightcourse = true;
                right_stu.push_back(stu);
              }
            }
          }
        }
      }
      if(rightcourse == false){
        continue;
      }
      std::vector<std::string> roster;
      roster.push_back(course);
      for(std::string str : right_stu){
        roster.push_back(str);
      }
      Correct_Roster.push_back(roster);
    }
  return Correct_Roster;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(V2D courses, std::vector<std::string> timeslots){
  V2D sched;

  Graph g;
  for (unsigned i = 0; i < courses.size() - 1; i++) {
    for (unsigned j = i+1; j < courses.size(); j++) {
      if (connected(courses, i, j)) {
        g.addEdge(courses[i][0], courses[j][0]);
      }
    }
  }

  std::vector<std::string> sequence;
  for (unsigned i = 0; i < courses.size(); i++) {
    sequence.push_back(courses[i][0]);
  }
  for (unsigned i = 0; i < sequence.size()-1; i++) {
    for (unsigned j = i+1; j < sequence.size(); j++) {
      if (g.getDegree(sequence[j]) > g.getDegree(sequence[i])) {
        std::swap(sequence[j], sequence[i]);
      }
    }
  }

  std::map<std::string, int> colorMap;
  for (std::string s : sequence) {
    colorMap[s] = -1; 
  }

  int currColor = 0;

  for (std::string s : sequence) {
    currColor = 0;
    while (1) {
      bool shouldContinue = false;
      for (std::string adjV : g.adjacentVertices(s)) {
        if (colorMap[adjV] == currColor) {
          shouldContinue = true;
          currColor++;
          break;
        }
      }
      if (!shouldContinue) {
        break;
      }
    }
    colorMap[s] = currColor;
  }

  for (auto it = colorMap.begin(); it != colorMap.end(); it++) {
    if (it->second > currColor) {
      currColor = it->second;
    }
  }

  if (currColor + 1 > (int)timeslots.size()) {
    std::vector<std::string> vec;
    vec.push_back("-1");
    sched.push_back(vec);
    return sched;
  }

  int color = 0;
  for (unsigned slot = 0; slot < timeslots.size() && color <= currColor; slot++) {
    std::vector<std::string> currSlot;
    currSlot.push_back(timeslots[slot]);
    for (auto it = colorMap.begin(); it != colorMap.end(); ++it) {
      if (it->second == color) {
        currSlot.push_back(it->first);
      }
    }
    sched.push_back(currSlot);
    color++;
  }

  return sched;
}

bool connected(const V2D & courses, unsigned m, unsigned n) {
  const std::vector<std::string> & roster1 = courses[m];
  const std::vector<std::string> & roster2 = courses[n];
  for (unsigned i = 1; i < roster1.size(); i++) {
    for (unsigned j = 1; j < roster2.size(); j++) {
      if (roster1[i] == roster2[j]) {
        return true;
      }
    }
  }
  return false;
}
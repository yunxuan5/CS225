/**
 * @file schedule.h
 * Exam scheduling using graph coloring
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>

typedef std::map<std::string, std::vector<std::string> > sMap;
typedef std::vector<std::vector<std::string> > V2D; 

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. <XXX: WORDING HERE?> 
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename);

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param course A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & sv);

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * If a valid solution cannot be formed after <XXX: How many iterations?> iterations of graph coloring, return a V2D with one row
 * with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(V2D courses, std::vector<std::string> timeslots);

bool connected(const V2D & courses, unsigned m, unsigned n);

class Graph {
    public:
        ~Graph() {
            for (auto it = adjList_.begin(); it != adjList_.end(); ++it) {
                EdgeNode * curr = it->second;
                while (curr != NULL) {
                    EdgeNode * temp = curr->next_;
                    delete curr;
                    curr = temp;
                }
            }
        }

        void addEdge(std::string v1, std::string v2) {
            if (edgeExists(v1, v2))
                return;
            addEdgeHelper_(v1, v2);
            addEdgeHelper_(v2, v1);
        }

        std::vector<std::string> adjacentVertices(std::string v) {
            EdgeNode * edges = adjList_[v];
            std::vector<std::string> ret_vec;
            while (edges != NULL) {
                ret_vec.push_back(edges->course_);
                edges = edges->next_;
            }
            return ret_vec;
        }

        int getDegree(std::string v) {
            return adjacentVertices(v).size();
        }

        // for testing
        friend void print_Graph(const Graph & g);

    private:
        struct EdgeNode {
            std::string course_;
            EdgeNode * next_;
        };

        std::map<std::string, EdgeNode *> adjList_;

        void addEdgeHelper_(std::string v1, std::string v2) {
            if (adjList_.find(v1) == adjList_.end()) {
                // map does not contain v1
                EdgeNode * newEdge = new EdgeNode;
                newEdge->course_ = v2;
                newEdge->next_ = NULL;
                adjList_[v1] = newEdge;
            } else {
                // map contains v1
                EdgeNode * newEdge = new EdgeNode;
                newEdge->course_ = v2;
                newEdge->next_ = adjList_[v1];
                adjList_[v1] = newEdge;
            }
        }

        bool edgeExists(std::string v1, std::string v2) {
            if (adjList_.find(v1) == adjList_.end()) {
                return false;
            }
            if (adjList_.find(v2) == adjList_.end()) {
                return false;
            }
            EdgeNode * edges1 = adjList_[v1];
            EdgeNode * edges2 = adjList_[v2];
            while (edges1 != NULL) {
                if (edges1->course_ == v2) {
                    return true;
                }
                edges1 = edges1->next_;
            }

            while (edges2 != NULL) {
                if (edges2->course_ == v1) {
                    return true;
                }
                edges2 = edges2->next_;
            }
            return false;
        }
};
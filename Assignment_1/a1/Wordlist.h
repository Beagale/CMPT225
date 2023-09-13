// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the doubly-linked list for the word list.
    // Don't change it any way!
    //
    struct Node
    {
        string word;
        int count;
        Node *next;
        Node *prev;
    };

    //
    // ... your code goes here ...
    //
   
    private:
        Node* header;
        Node* trailer;


    public:
        
        bool flag_isFrozen = false;

        // Wordlist constructor
        // Utilized/referenced code from txt. book: Data Structures and Algorithms 2nd Edition pg 126
        // Referenced code from https://www.scaler.com/topics/doubly-linked-list-cpp/ for creating the header and trailer
        Wordlist(){
            // TEST
            cout << "Constructing empty Wordlist" << endl;
            header = new Node();
            trailer = new Node();

            header = nullptr;
            trailer = nullptr;

            // header->next = trailer;
            // trailer->prev = header; // NOT SURE ABOUT THIS
        }

        // Wordlist copy constructor
        // Utilized/referenced code from https://www.tutorialspoint.com/cplusplus/cpp_copy_constructor.htm on copy constructors
        // Wordlist(const Wordlist& other){
        //     header = new Node();
        //     trailer = new Node();

        //     Node *temp = new Node();

        //     // Copy the value of the header in other
        //     *header = *other.header;
        //     *trailer = *other.trailer;

        //     while(header->next != NULL){
        //         header = other.header->next; 


        //     }
        //     header->next = trailer;
        //     trailer->prev = header;
        // }

        // Function to check if Wordlist is frozen
        bool is_frozen() const{
            if (flag_isFrozen == false){
                return false;
            }
            else{
                return true;
            }
        }

        // Utilized/referenced code from https://www.alphacodingskills.com/cpp/ds/cpp-doubly-linked-list-search-an-element.php 
        bool contains(const string &w) const{
            Node* temp = header;
            // Create a flag called containsWord that gets updated if word w is found in list
            bool containsWord = false;
            if (temp != NULL){
                // Loop through list until we reach the end
                while (temp != NULL){
                    if (temp->word == w){
                        containsWord = true;
                        
                        break;
                    }
                    temp = temp->next;
                }
            }

            // delete temp;
            return containsWord;
        }


        //
        // Pre-condition:
        //    0 <= index < length()
        // Post-condition:
        //    Returns a copy of the word at the given index.
        // Performance:
        //    It's worst-case running time should be proportional to the length of
        //    the list (or better).
        //
        string get_word(int index) const{
            int counter = 0;
            string word_found = "";
            // Check if index is equal to 0 or less than the length of the Wordlist
            if (index >= 0 && index < length()){
                Node* temp = header;
                if (temp != NULL){
                    while (temp != NULL){
                        if (counter == index){
                            word_found = temp->word;
                        }
                        temp = temp->next;
                        counter++;
                    }
                }

                delete temp;
            }
            else{
                cout << "Index is invalid" << endl;
            }

            return word_found;

        }

        //
        // Pre-condition:
        //    !is_frozen()
        // Post-condition:
        //    If w is not in the list already, adds w to the end of the list.
        //    If w is already in the list, does nothing.
        // Performance:
        //    It's worst-case running time should be proportional to the length of
        //    the list (or better).
        //

        // Utilized/referenced code from https://www.alphacodingskills.com/cpp/ds/cpp-doubly-linked-list-search-an-element.php 
        // Function add a word to the list
        void add_word(const string &w){
            // Precondition: make sure that is_frozen() returns false;
            if (is_frozen() == false){
                // Check if word w is in the Wordlist already
                bool wordIsThere = false; 
                wordIsThere = contains(w);
                if (wordIsThere == true){
                    return; 
                }
                else{
                    // Create a new node that has the word w
                    Node* addedWord = new Node;
                    // Set the node to have its word be w
                    addedWord->word = w;
                    // Set the new node's previous and next nodes to be null
                    addedWord->next = nullptr;
                    addedWord->prev = nullptr;

                    // If the Wordlist is empty, make the new added word the header
                    if (header == nullptr){
                        header = addedWord;
                    }
                    // Traverse to the end of the list, then add the new word into the end of list
                    else{
                        Node* temp = header;
                        while (temp->next != NULL){
                            temp = temp->next;
                        }
                        temp->next = addedWord;
                        addedWord->prev = temp;
                        // delete addedWord;
                        // delete temp;
                
                    }     

                }
               
            }
            else{
                throw runtime_error("ERROR: Cannot add word to frozen list");
                cout << endl;
            }

            
                      
        }

         //
        // Pre-condition:
        //    !is_frozen()
        // Post-condition:
        //    Removes all occurrences of w from the word list. If w is not in the
        //    list, then does nothing.
        // Performance:
        //    It's worst-case running time should be proportional to the length of
        //    the list (or better).
        //
        void remove_word(const string &w){
            // Precondition: make sure that is_frozen() returns false;
            if (is_frozen() == false){
                // Check if word w is in the Wordlist already
                bool wordIsThere = false; 
                wordIsThere = contains(w);
                if (wordIsThere == false){
                    // TEST
                    cout << "Word is NOT in list" << endl;
                    return; 
                }
                else{
                    // TEST
                    cout << "Word is in list" << endl;
                    Node* temp = header;

                    while (temp != nullptr){
                        temp = temp->next;
                    }

                    Node* u = temp->prev;
                    Node* w = temp->prev->prev;

                    u->next = nullptr;
                    u->prev = w;
                    // w->prev = u;
                    delete temp;
                   
                }
                
            }
            else{
                throw runtime_error("ERROR: Cannot add word to frozen list");
                cout << endl;
            }

        }

        
        // Wordlist deconstructor
        // Utilized code from user "cire" on Mar 2, 2015 on cplusplus forum: https://cplusplus.com/forum/general/158547/
        ~Wordlist(){
            // TEST
            cout << "Deconstructing Wordlist" << endl;

            // Create a temp Node pointer and make it equal to sentinel header
            Node *temp = header;

            // Traverse through doubly linked list using temp pointer
            while (temp != NULL){
                // Create a new Node pointer called next and have it equal to the next node to pointer temp
                Node* next = temp->next;
                // Delete the original temp pointer to free its memory
                delete temp;
                // Set the temp pointer to next (the next node to the original temp)
                temp = next;
            }
                
        }

        // Function to return total number of nodes in list
        // Utilized/referenced code from https://www.alphacodingskills.com/cpp/ds/cpp-doubly-linked-list-traversal.php 
        int length() const{
            int counter = 0;
            Node* temp = header;

            // Check if list is NOT empty first
            if (temp != NULL){
                while(temp != NULL){
                    // Incremenet counter as we visit each node in the list until we've reached the end of list
                    counter++;
                    temp = temp->next;
                }
            }
            // if (counter == 2){
            //     cout << "Sorry, there are no nodes in the list." << endl;
            //     counter = 0;
            // }
            
            // TEST
            //cout << counter << endl;

            delete temp;
            return counter;

        }


        void printWordlist(){
            Node* temp = header;
            cout << endl << "The list: ";
            if (temp != nullptr){
                while (temp != nullptr){
                    cout << temp->word << " ";
                    temp = temp->next;
                }
            }

            cout << endl;

            delete temp;
            return;
        }
        // Utilized/referenced code from txt. book: Data Structures and Algorithms 2nd Edition pg 128 for the following 3 functions:
        // Helper function to remove node from front of list
        // void removeFront();
        // // Helper function to remove node form back of list
        // void removeBack();
        // // Helper function to remove nodes from list
        // void remove(Node* v);

 
       

      
    //
    // ... you can write helper methods if you need them ...
    //


}; // class Wordlist

//
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//

// void Wordlist::removeFront(){
//     remove(header->next);
// }

// void Wordlist::removeBack(){
//     remove(trailer->prev);
// }

// void Wordlist::remove(Node* v){
//     // Store node v's previous node in node u
//     Node* u = v->prev;
//     // Store node v's next node in node w
//     Node* w = v->next;
//     // Move node u and w in proper place before removing node v
//     u->next = w;
//     w->prev = u;

//     delete v;

   
// }

 // if (1)
    // {
    //     throw runtime_error("Whoops!");
    // } 

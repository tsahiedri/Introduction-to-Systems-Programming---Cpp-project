#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <iostream>
#include <stdexcept>

namespace mtm {

    /** A class that represents the linked list.
     * It holds a pointer to the beginning of the list and the list's length.*/
    template<class T>
    class SortedList {
    private:
        /** A class that represents a vertex in the list.
        * On each node there's information about the data it holds, and pointers to the next and previous nodes.*/
        class Node {
        private:
            T data;
            Node* next;
            Node* previous;
        public:
            explicit Node(T data, Node* next = nullptr, Node* previous = nullptr) :
                data(data), next(next), previous(previous) {}

            ~Node() = default;

            /** A method that returns the data in the node. */

            const T& getData() const
            {
                return data;
            }



            /** A method that returns a pointer to the next node. */
            Node* getNext() const
            {
                return next;
            }

            /** A method that sets the pointer to the next node. */
            void setNext(Node* new_next)
            {
                next = new_next;
            }

            /** A method that returns a pointer to the previous node. */
            Node* getPrevious() const
            {
                return previous;
            }

            /** A method that sets the pointer to the previous node. */
            void setPrevious(Node* new_previous)
            {
                previous = new_previous;
            }
        };

        Node *head;
        int len;

        public:

        /** A class that represents a constant iterator that can be used to go over the linked list.*/
        class const_iterator {
        private:
            Node *pointer;

            explicit const_iterator(Node *pointer = nullptr) : pointer(pointer) {}

        public:
            const_iterator(const const_iterator &) = default;

            const_iterator &operator=(const const_iterator &) = default;

            ~const_iterator() = default;

            /** Overloading the '++' operator. It will now move the iterator to point on the next node in the list. */
            const_iterator &operator++()
            {
                if (pointer == nullptr)
                {
                    throw std::out_of_range("");
                }
                pointer = pointer->getNext();
                return *this;
            }

            /** Overloading the '==' operator. It will now check if two iterators are pointing on the same node.*/
            bool operator==(const const_iterator &iterator) const
            {
                return (iterator.pointer == pointer);
            }

            /** Overloading the '*' operator. It will now return the data that the pointed node holds.
             * The data is returned by a constant reference.*/
            const T &operator*()
            {
                if (pointer == nullptr)
                {
                    throw std::out_of_range("");
                }
                return pointer->getData();
            }

            /** A method that creates a const iterator pointing to the beginning of the list, and returns it.*/
            friend const_iterator SortedList::begin() const;

            /** A method that creates a const iterator pointing to the end of the list, and returns it.*/
            friend const_iterator SortedList::end() const;

            /** A method that will be used to remove a node from the list. */
            friend void SortedList::remove(const_iterator to_destroy);
        };

        SortedList() : head(nullptr), len(0) {}

        ~SortedList()
        {
            while (!(begin() == end())) {
                remove(begin());
            }
        }

        SortedList(const SortedList &list) : head(nullptr), len(0)
        {
            for (const_iterator iterator = list.begin(); !(iterator == list.end()); ++iterator)
            {
                insert(*iterator);
            }
        }

        /** Overloading the assigment operator ('=').*/
        SortedList &operator=(const SortedList &list)
        {
            if (this == &list)
            {
                return *this;
            }
            while (!(begin() == end()))
            {
                remove(begin());
            }
            for (const_iterator iterator = list.begin(); !(iterator == end()); ++iterator)
            {
                insert(*iterator);
            }
            return *this;
        }

        /** A method that creates a new node with the given data and places it at its place.*/
        void insert(const T &data)
        {
            if (head == nullptr || (data < head->getData()))
            {
                Node *new_head = new Node(data, head);
                if (head != nullptr)
                {
                    head->setPrevious(new_head);
                }
                head = new_head;
                len++;
                return;
            }
            Node *current = head;
            Node *last;
            while (current != nullptr)
            {
                if (data < current->getData())
                {
                    break;
                }
                last = current;
                current = current->getNext();
            }
            last->setNext(new Node(data, current, last));
            if (current != nullptr)
            {
                current->setPrevious(last->getNext());
            }
            len++;
        }

        /** A method that will be used to remove a node from the list. */
        void remove(const_iterator to_destroy)
        {
            if (to_destroy == end())
            {
                return;
            }
            Node *node_to_destroy = to_destroy.pointer;
            if (to_destroy == begin())
            {
                head = node_to_destroy->getNext();
                if (node_to_destroy->getNext() != nullptr)
                {
                    node_to_destroy->getNext()->setPrevious(nullptr);
                }
                delete (node_to_destroy);
                len--;
                return;
            }
            if (node_to_destroy->getNext() != nullptr)
            {
                node_to_destroy->getNext()->setPrevious(node_to_destroy->getPrevious());
            }
            node_to_destroy->getPrevious()->setNext(node_to_destroy->getNext());
            delete (node_to_destroy);
            len--;
        }

        int length() const
        {
            return len;
        }

        /** A method that receives a predicate (Boolean function) on the type of list members, and returns a new list
            which contains only the organs from the original list that satisfy the condition. */
        template<class S>
        SortedList filter(S condition) const
        {
            SortedList<T> new_list;
            for (const_iterator iterator = begin(); !(iterator == end()); ++iterator)
            {
                if (condition(*iterator) == true)
                {
                    new_list.insert(*iterator);
                }
            }
            return new_list;
        }

        /** A method that receives a function, and returns a new SortedList object which is the result of applying the
         *  given function on all the organs from the original list.*/
        template<class S>
        SortedList apply(S function) const
        {
            SortedList<T> new_list;
            for (const_iterator iterator = begin(); !(iterator == end()); ++iterator)
            {
                new_list.insert(function(*iterator));
            }
            return new_list;
        }

        /** A method that creates a const iterator pointing to the beginning of the list, and returns it.*/
        const_iterator begin() const
        {
            return const_iterator(head);
        }

        /** A method that creates a const iterator pointing to the end of the list, and returns it.*/
        const_iterator end() const
        {
            return const_iterator(nullptr);
        }
    };
}

#endif // SORTED_LIST_H
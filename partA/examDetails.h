#ifndef EXAM_DETAILS_H
#define EXAM_DETAILS_H

#include <iostream>
#include <string>

using std::string;

namespace mtm{

    /** A class that represents an exam in the system.*/
    class ExamDetails{
    private:
        int course_num;
        int month;
        int day;
        double hour;
        int exam_len;
        string zoom_link;
        int full_hour;
        int minutes;
    public:
        ExamDetails(int course_num, int month, int day, double hour, int exam_len, string zoom_link = "");
        ~ExamDetails()=default;
        ExamDetails(const ExamDetails& exam)=default;
        ExamDetails& operator=(const ExamDetails& exam)=default;

        /** A method that returns the zoom link for the given exam.*/
        string getLink() const
        {
            return zoom_link;
        }

        /** A method that sets the zoom link for the given exam.*/
        void setLink(string new_link)
        {
            zoom_link = new_link;
        }

        /** Overloading the '-' operator. It will now return the time difference (in days) between two exams.*/
        int operator-(const ExamDetails& exam) const
        {
            return  (month*30+day)-(exam.month*30+exam.day);
        }

        /** Overloading the '<' operator. It will now return true if the first exam happens before the second one.*/
        bool operator<(const ExamDetails& exam) const
        {
            if ((*this - exam) < 0)
            {
                return true;
            }
            else if ((*this - exam) == 0)
            {
                return(hour < exam.hour);
            }
            return false;
        }

        /** Overloading the '<<' operator that will be used to print the exam details. 
         * The details will be printed in the following format (without apostrophes):
         * " Course Number: <course number>
         *   Time: <exam day>.<exam month> at <exam time (hour:minutes)>
         *   Duration: <exam duration (hours:00)>
         *   Zoom Link: <exam's zoom link> "
         * When the words in <> are replaced by the actual information */
        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

        /** A static method that creates an ExamDetails object that represents the MATAM exam. */
        static ExamDetails makeMatamExam();

        /** Exceptions classes that are implemented using inheritance from std::exception.
         * The following exceptions will be thrown by the constructor at the following cases:
         * InvalidDateException - In case the given date isn't valid. This will happen if the given month isn't between
         *                        1 and 12, or if the given day isn't between 1 and 30.
         * InvalidTimeException - In case the given time is not valid. This will happen if the given exam starting hour
         *                        isn't between 0 and 24 or if it isn't a round hour or some hour and a half 
         *                        (an exam can begin in 6:00 or 13:30, but can't begin in 18:15).
         *                        Will be checked with a precision of 10e-6.*/
        class Exception : public std::exception {};
        class  InvalidDateException : public Exception {};
        class InvalidTimeException : public Exception {};
    };

}

#endif //EXAM_DETAILS_H
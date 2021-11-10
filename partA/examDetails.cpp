#include <iostream>
#include <string>
#include <cmath>
#include "examDetails.h"

namespace mtm{
    ExamDetails::ExamDetails(int course_num, int month, int day, double hour, int exam_len, std::string zoom_link):
    course_num(course_num), month(month), day(day), hour(hour), exam_len(exam_len), zoom_link(zoom_link)
    {
        if(month<1 || month>12 || day<1 || day>30)
        {
            throw ExamDetails::InvalidDateException();
        }
        if(hour<0 || hour>=24)
        {
            throw ExamDetails::InvalidDateException();
        }
        double temp_full_hour, hour_frac;
        hour_frac=std::modf(hour, &temp_full_hour);
        full_hour=(int)temp_full_hour;
        int const epsilon = 10e-6;
        if (hour_frac >= -epsilon && hour_frac <= epsilon )
        {
            minutes=0;
        }
        else if (hour_frac >= (0.5 - epsilon) && hour_frac <= (0.5 + epsilon))
        {
            minutes=30;
        }
        else
        {
            throw ExamDetails::InvalidTimeException();
        }
    }

    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam)
    {
        return os<<"Course Number: "<<exam.course_num<<std::endl<<"Time: "<<exam.day<<"."<<exam.month<<" at "<<
            exam.full_hour<<":"<<exam.minutes/10<<"0"<<std::endl<<"Duration: "<<exam.exam_len<<":00"<<std::endl<<
            "Zoom Link: "<<exam.zoom_link<<std::endl;
    }

    ExamDetails ExamDetails::makeMatamExam()
    {
        return ExamDetails(234124,7,28, 13.00,3, "https://tinyurl.com/59hzps6m");
    }
    }





#ifndef SORT_HEADER
#define SORT_HEADER

/*! Enum class describing the possible sorting options.*/
enum class Sort
{
    None = 0,/*!< No sorting*/
    Name = 1, /*!< Sort by Name, ascending.*/
    Length = 2,/*!< Sort by Length, ascending.*/
    AvgWorkoutTime = 3,/*!< Sort by AvgWorkoutTime, ascending.*/
    Difficulty = 4,/*!< Sort by Difficulty, ascending.*/
    Name_Descending = 5,/*!< Sort by Name, descending.*/
    Length_Descending = 6,/*!< Sort by Length, descending.*/
    AvgWorkoutTime_Descending = 7,/*!< Sort by AvgWorkoutTime, descending.*/
    Difficulty_Descending = 8/*!< Sort by Difficulty, descending.*/
};
#endif
#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>
#include <vector>
#include <memory>
#include <jansson.h>


/*! Namespace containing the models which describe the data used by this application.*/
namespace Models
{
/*! Model describing an **user** of this service. A User who failed authentication is invalid.*/
class User
{
  private:
    std::string displayName;
    unsigned int id;

    const bool verified;

  public:
    const std::string &getDisplayName() const;
    unsigned int getID() const;
    bool isValid() const;
    User(const std::string &displayName, const unsigned int &id);
    /*! Makes an **invalid** user. Use to indicate if authentication failed.*/
    User(bool verified);
};

/*! Model for the basic building block of a workout plan.*/
class Exercise
{
  public:
  /*! Enum class, the type of the Models::Exercise*/
    enum class Type
    {
        RepsOnly = 0, /*!<Exercise only tracks repetitions. */
        WeightOnly = 1, /*!<Exercise only tracks weight used. */
        RepsAndWeight = 2, /*!<Exercise tracks both repetitions and weight used. */
        JustDone = 3, /*!<Exercise can only be done or not done. */
        Invalid = -1  /*!<Exercise couldn't be parsed as any of the above, and therefore is invalid. */
    };

    Exercise(const std::string &name, const std::string &note, Type type, const std::string &reps, const std::string &weight, const bool &done);
    /*!\return a string representation of the JSON representation of the Exercise.*/
    std::string toJSON();

    bool isDone() const {return done;}
    std::string getName() const {return name;}
    std::string getNote() const {return note;}
    std::string getWeight() const {return weight;}
    std::string getReps() const {return reps;}
    Type getType() const {return type;}

  private:
    std::string name;
    std::string note;
    Type type;
    std::string reps;
    std::string weight;
    bool done;
};

/*! Model of a workout, a collection of Models::Exercises, distinguished in time by being in the morning, day or evening.*/
class Workout
{
  public:
  /*!Enum class. The time of the Models::Workout*/
    enum class TimeOfDay
    {
        Morning = 0,
        Day = 1,
        Evening = 2,
        Invalid = -1/*!<The time is none of the above, and therefore invalid.*/
    };
    /*! \param string one of: morning, Morning, day, Day, midday, Midday, evening, Evening, night, Night
    \return the time corresponding to the **string** parameter
    
    Construct a Models::Workout::TimeOfDay from a string representation.*/
    static Models::Workout::TimeOfDay timeFromString(const std::string & string);

    Workout(const std::string &name, const std::string &description, const TimeOfDay &time, const bool &done , const bool & skipped);
    /*!\return a string representation of the JSON representation of the Workout.*/
    std::string toJSON();
    /*!\param exercise the Models::Exercise to add.

    Add the **Exercise** to this Workout.*/
    void addExercise(Exercise exercise);
    TimeOfDay getTime()const{return time;}

  private:
    std::string name;
    std::string description;
    bool done;
    bool skipped;
    TimeOfDay time;
    std::vector<Exercise> exercises;
};

/*! Model for a day. May contain up to 3 Exercises, one each of TimeOfDay morning, day and evening.*/
class Day
{
  public:
  /*!The days of the week.*/
    enum class Days
    {
        Monday = 0,
        Tuesday = 1,
        Wednesday = 2,
        Thursday = 3,
        Friday = 4,
        Saturday = 5,
        Sunday = 6,
        Invalid = -1 /*!<Day could not be interpreted as any of the above, and therefore is invalid.*/
    };
    /*!\return the string representation of the Days*/
    std::string dayAsString(const Days & day);
    /*!\param string the string representation of a Days
    \return a Days parsed from string*/
    static Days fromString(const std::string & string); 

    //for sorting
    bool operator<(const Day & other){return this->dayOfTheWeek<other.dayOfTheWeek;}
    bool operator>(const Day & other){return this->dayOfTheWeek>other.dayOfTheWeek;}
    bool operator<=(const Day & other){return this->dayOfTheWeek<=other.dayOfTheWeek;}
    bool operator>=(const Day & other){return this->dayOfTheWeek>=other.dayOfTheWeek;}
    bool operator==(const Day & other){return this->dayOfTheWeek==other.dayOfTheWeek;}

    Day(const Days & dayOfTheWeek);
    /*!\param workout the Workout to add

    Add a Workout to this day. Only one Workout of each valid TimeOfDay can be present, otherwise this will **overwrite** the old Workout.*/
    void addWorkout(Workout workout);
    /*!\return a string representation of the JSON representation of the Day.*/
    std::string toJSON();

  private:
    Days dayOfTheWeek;
    std::shared_ptr<Workout> morning;
    std::shared_ptr<Workout> midday;
    std::shared_ptr<Workout> evening;
};
/*!Model of a Week, a vector of Day*/
class Week
{
  public:
    void addDay(Day day);

    /*!\return a string representation of the JSON representation of the Week.*/
    std::string toJSON();

  private:
    std::vector<Day> days;
};

/*! Model for the Worksheet, the top level of our data hierarchy. Encapsulates a vector of Weeks.*/
class Worksheet
{
  public:
    Worksheet(const std::string &name, const std::string &description, const std::string &avgWorkoutLength, const std::string &difficulty);
    /*! \param week the Week to add

    Adds the Week to this Worksheet.*/
    void addWeek(Week week);
    /*!\return a string representation of the JSON representation of the Worksheet.*/
    std::string toJSON();

  private:
    std::string name;
    std::string description;
    std::string avgWorkoutLength;
    std::string difficulty;
    std::vector<Week> weeks;
};
}
#endif
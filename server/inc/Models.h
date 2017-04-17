#ifndef MODELS_HEADER
#define MODELS_HEADER

#include <string>
#include <vector>
#include <memory>
#include <jansson.h>

namespace Models
{
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
    User(bool verified);
};

class Exercise
{
  public:
    enum class Type
    {
        RepsOnly = 0,
        WeightOnly = 1,
        RepsAndWeight = 2,
        JustDone = 3,
        Invalid = -1
    };

    Exercise(const std::string &name, const std::string &note, Type type, const std::string &reps, const std::string &weight, const bool &done);
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

class Workout
{
  public:
    enum class TimeOfDay
    {
        Morning = 0,
        Day = 1,
        Evening = 2,
        Invalid = -1
    };

    static Models::Workout::TimeOfDay timeFromString(const std::string & string);

    Workout(const std::string &name, const std::string &description, const TimeOfDay &time, const bool &done , const bool & skipped);
    std::string toJSON();
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

class Day
{
  public:
    enum class Days
    {
        Monday = 0,
        Tuesday = 1,
        Wednesday = 2,
        Thursday = 3,
        Friday = 4,
        Saturday = 5,
        Sunday = 6,
        Invalid = -1
    };
    std::string dayAsString(const Days & day);
    static Days fromString(const std::string & string); 

    //for sorting
    bool operator<(const Day & other){return this->dayOfTheWeek<other.dayOfTheWeek;}
    bool operator>(const Day & other){return this->dayOfTheWeek>other.dayOfTheWeek;}
    bool operator<=(const Day & other){return this->dayOfTheWeek<=other.dayOfTheWeek;}
    bool operator>=(const Day & other){return this->dayOfTheWeek>=other.dayOfTheWeek;}
    bool operator==(const Day & other){return this->dayOfTheWeek==other.dayOfTheWeek;}

    Day(const Days & dayOfTheWeek);
    void addWorkout(Workout workout);
    std::string toJSON();

  private:
    Days dayOfTheWeek;
    std::shared_ptr<Workout> morning;
    std::shared_ptr<Workout> midday;
    std::shared_ptr<Workout> evening;
};

class Week
{
  public:
    void addDay(Day day);
    std::string toJSON();

  private:
    std::vector<Day> days;
};

class Worksheet
{
  public:
    Worksheet(const std::string &name, const std::string &description, const std::string &avgWorkoutLength, const std::string &difficulty);
    void addWeek(Week week);
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
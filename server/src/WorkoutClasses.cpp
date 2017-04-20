#include <Models.h>

Models::Exercise::Exercise(const std::string &name, const std::string &note, Models::Exercise::Type type, const std::string &reps, const std::string &weight, const bool &done)
    : name(name), note(note), type(type), reps(reps), weight(weight), done(done) {}

std::string Models::Exercise::toJSON()
{
    json_t *root = json_object();

    json_object_set_new(root, "name", json_string(name.c_str()));
    json_object_set_new(root, "note", json_string(note.c_str()));

    switch (type)
    {
    case Models::Exercise::Type::JustDone:
        json_object_set_new(root, "done", json_boolean(done));
        break;
    case Models::Exercise::Type::RepsOnly:
        json_object_set_new(root, "R",json_string(reps.c_str()));
        break;
    case Models::Exercise::Type::WeightOnly:
        json_object_set_new(root, "W",json_string(weight.c_str()));
        break;
    case Models::Exercise::Type::RepsAndWeight:
        json_object_set_new(root, "W",json_string(weight.c_str()));
        json_object_set_new(root, "R",json_string(reps.c_str()));
        break;
    }

    char *raw = json_dumps(root, 0);
    std::string json(raw);
    delete raw;

    json_decref(root);
    return json;
}

Models::Workout::Workout(const std::string &name, const std::string &description, const TimeOfDay &time, const bool &done, const bool & skipped)
    : name(name), description(description), time(time), done(done), skipped(skipped) {}

std::string Models::Workout::toJSON()
{
    json_t *root = json_object();
    json_t *exercises = json_array();

    json_object_set_new(root, "name", json_string(name.c_str()));
    json_object_set_new(root, "description", json_string(description.c_str()));
    switch (time)
    {
    case Models::Workout::TimeOfDay::Morning:
        json_object_set_new(root, "time", json_string("morning"));
        break;
    case Models::Workout::TimeOfDay::Day:
        json_object_set_new(root, "time", json_string("day"));
        break;
    case Models::Workout::TimeOfDay::Evening:
        json_object_set_new(root, "time", json_string("night"));
        break;
    }
    json_object_set_new(root, "done", json_boolean(done));
    json_object_set_new(root, "skipped", json_boolean(skipped));

    for (auto &exercise : this->exercises)
    {
        json_error_t err;
        json_t *tmp = json_loads(exercise.toJSON().c_str(), 0, &err);
        json_array_append(exercises, tmp);
        json_decref(tmp);
    }

    json_object_set_new(root, "exercises", exercises);

    char *raw = json_dumps(root, 0);
    std::string json(raw);
    delete raw;

    json_decref(root);
    return json;
}

void Models::Workout::addExercise(Exercise exercise)
{
    this->exercises.push_back(exercise);
}
    
Models::Workout::TimeOfDay Models::Workout::timeFromString(const std::string & string){
    if("Morning"==string || "morning"==string){return Models::Workout::TimeOfDay::Morning;}
    if("Day"==string || "day"==string || "Midday"==string || "midday"==string){return Models::Workout::TimeOfDay::Day;}
    if("Evening"==string || "evening"==string || "Night"==string || "night"==string){return Models::Workout::TimeOfDay::Evening;}
    return Models::Workout::TimeOfDay::Invalid;
}

Models::Day::Day(const Days &dotw) : dayOfTheWeek(dotw)
{
    morning = 0;
    midday = 0;
    evening = 0;
}

std::string Models::Day::toJSON()
{
    json_t *root = json_object();
    json_t *workouts = json_array();

    json_object_set_new(root, "day", json_string(dayAsString(this->dayOfTheWeek).c_str()));

    if (morning != 0)
    {
        json_error_t err;
        json_t *tmp = json_loads(morning->toJSON().c_str(), 0, &err);
        json_array_append(workouts, tmp);
        json_decref(tmp);
    }
    if (midday != 0)
    {
        json_error_t err;
        json_t *tmp = json_loads(midday->toJSON().c_str(), 0, &err);
        json_array_append(workouts, tmp);
        json_decref(tmp);
    }
    if (evening != 0)
    {
        json_error_t err;
        json_t *tmp = json_loads(evening->toJSON().c_str(), 0, &err);
        json_array_append(workouts, tmp);
        json_decref(tmp);
    }

    json_object_set_new(root, "workouts", workouts);

    char *raw = json_dumps(root, 0);
    std::string json(raw);
    delete raw;

    json_decref(root);
    return json;
}

void Models::Day::addWorkout(Workout workout)
{
    switch (workout.getTime())
    {
    case Models::Workout::TimeOfDay::Morning:
        morning =std::make_shared<Workout>(workout);
        break;
    case Models::Workout::TimeOfDay::Day:
        midday = std::make_shared<Workout>(workout);
        break;
    case Models::Workout::TimeOfDay::Evening:
        evening = std::make_shared<Workout>(workout);
        break;
    }
}

std::string Models::Day::dayAsString(const Days &day)
{
    switch (day)
    {
    case Models::Day::Days::Monday:
        return "Monday";
    case Models::Day::Days::Tuesday:
        return "Tuesday";
    case Models::Day::Days::Wednesday:
        return "Wednesday";
    case Models::Day::Days::Thursday:
        return "Thursday";
    case Models::Day::Days::Friday:
        return "Friday";
    case Models::Day::Days::Saturday:
        return "Saturday";
    case Models::Day::Days::Sunday:
        return "Sunday";
    case Models::Day::Days::Invalid:
        return "Invalid day.";
    }
    return "ERROR";
}

Models::Day::Days Models::Day::fromString(const std::string & string){
    if(string=="Monday" || "monday"==string){return Models::Day::Days::Monday;}
    if(string=="Tuesday" || "tuesday"==string){return Models::Day::Days::Tuesday;}
    if(string=="Wednesday" || "wednesday"==string){return Models::Day::Days::Wednesday;}
    if(string=="Thursday" || "thursday"==string){return Models::Day::Days::Thursday;}
    if(string=="Friday" || "friday"==string){return Models::Day::Days::Friday;}
    if(string=="Saturday" || "saturday"==string){return Models::Day::Days::Saturday;}
    if(string=="Sunday" || "sunday"==string){return Models::Day::Days::Sunday;}
    return Models::Day::Days::Invalid;
}

void Models::Week::addDay(Day day)
{
    this->days.push_back(day);
}

std::string Models::Week::toJSON()
{
    std::string json("[");
    bool first = true;
    for (auto &day : days)
    {
        if (!first)
        {
            json.append(",");
        }
        first = false;
        json.append(day.toJSON());
    }
    json.append("]");
    return json;
}

Models::Worksheet::Worksheet(const std::string &name, const std::string &description, const std::string &avgWorkoutLength, const std::string &difficulty)
    : name(name), description(description), avgWorkoutLength(avgWorkoutLength), difficulty(difficulty) {}

void Models::Worksheet::addWeek(Week week)
{
    this->weeks.push_back(week);
}

std::string Models::Worksheet::toJSON()
{
    json_t *root = json_object();

    json_object_set_new(root, "name", json_string(this->name.c_str()));
    json_object_set_new(root, "description", json_string(this->description.c_str()));
    json_object_set_new(root, "difficulty", json_string(this->difficulty.c_str()));
    json_object_set_new(root, "avgWorkoutLength", json_string(this->avgWorkoutLength.c_str()));

    json_t *weeks = json_array();
    for (auto week : this->weeks)
    {
        json_error_t err;
        json_t *tmp = json_loads(week.toJSON().c_str(), 0, &err);

        json_array_append(weeks, tmp);
        json_decref(tmp);
    }

    json_object_set_new(root, "weeks", weeks);

    char *raw = json_dumps(root, 0);
    std::string json(raw);
    delete raw;

    json_decref(root);
    return json;
}
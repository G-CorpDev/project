import React, {Component} from 'react';
import axios from 'axios';

class Worksheet extends Component {
    constructor(props) {
        super(props);
        this.state = {
            sheet: require("../../json/test.json"),
            description: false,
            id: props.id,
            exercises: [],
            skippedExercises: [],
        };
    }

    componentDidMount() {
        this.getWorksheet();
        console.log("mounting");
    }

    setBlankExercise(sheet) {
        let _this = this;
        let firstUndone = true;
        let BreakException = {};
        try {
            sheet.weeks.forEach(function (week) {
                week.forEach(function (day) {
                    day.workouts.forEach(function (workout) {
                        if (firstUndone && !workout.done) {
                            let exs = workout.exercises.slice();
                            _this.setState({exercises: exs, skippedExercises: exs});
                            firstUndone = false;
                            throw BreakException;
                        }
                    });
                });
            });
        } catch (e) {
            if (e !== BreakException) console.log(e);
        }
    }

    getWorksheet() {
        let _this = this;
        axios.get('http://localhost:3000/users/' + _this.state.id + '/worksheet')
            .then(function (response) {
                console.log(response);
                _this.setState({sheet: response.data});
                _this.setBlankExercise(response.data);
            })
            .catch(function (error) {
                console.log(error);
                _this.setBlankExercise(_this.state.sheet);
            });
    }

    postExercises(week, day, time, exercises) {
        let _this = this;
        axios.post('http://localhost:3000/users/' + _this.state.id + '/finishWorkout',
            {week: week, day: day, time: time, exercises: exercises})
            .then(function (response) {
                console.log(response);
                //window.alert("Workout sent!");
                _this.getWorksheet();
            })
            .catch(function (error) {
                console.log(error);
                //window.alert(error);
            });
    }

    send(week, day, time, done) {
        console.log("sending data...");
        if (done === "skip") {
            this.postExercises(week, day, time, this.state.skippedExercises);
        } else {
            this.postExercises(week, day, time, this.state.exercises);
        }
    }

    handleInputChange(exerciseIndex, event) {
        const target = event.target;
        const value = target.type === 'checkbox' ? target.checked : target.value;
        const name = target.name;

        let jsonData = JSON.parse(JSON.stringify(this.state.exercises[exerciseIndex]));
        jsonData[name] = value;
        let exercises = this.state.exercises.slice();
        exercises[exerciseIndex] = jsonData;

        this.setState({
            exercises: exercises,
        });
    }

    renderExercise(exercise, index) {
        let W = "";
        if (exercise.hasOwnProperty('W')) {
            W = <input type="text" name="W" placeholder="W"
                       onChange={this.handleInputChange.bind(this, index)}/>;
        }
        let R = "";
        if (exercise.hasOwnProperty('R')) {
            R = <input type="text" name="R" placeholder="R"
                       onChange={this.handleInputChange.bind(this, index)}/>;
        }
        let done = "";
        if (exercise.hasOwnProperty('done')) {
            done = [<input type="checkbox" name="done" key="i"
                           onChange={this.handleInputChange.bind(this, index)}/>,
                <label className="exercise__checkbox" key="l">
                    <div>L</div>
                </label>];
        }
        return (
            <div className="exercise" key={index}>
                <input type="checkbox" id="note" className="exercise__addNoteInput"/>
                <label className="exercise__addNote" htmlFor="note">Note</label>
                <div className="exercise__basic">
                    <div className="exercise__name">
                        {exercise.name}:
                    </div>
                    <div className="exercise__inputs">
                        {W}
                        {R}
                        {done}
                    </div>
                </div>
                <input className="exercise__note" type="text" name="Note" placeholder="note"
                       onChange={this.handleInputChange.bind(this, index)}/>
            </div>
        )
    }

    renderTodoExercise(exercise, index) {
        let W = "";
        if (exercise.hasOwnProperty('W')) {
            W = <div className="weight">W</div>
        }
        let R = "";
        if (exercise.hasOwnProperty('R')) {
            R = <div className="reps">R</div>
        }
        let done = "";
        if (exercise.hasOwnProperty('done')) {
            done = <div className="done">X</div>
        }
        return (
            <div className="exercise" key={index}>
                <div className="exercise__basic">
                    <div className="exercise__name">
                        {exercise.name}:
                    </div>
                    <div className="exercise__inputs">
                        {W}
                        {R}
                        {done}
                    </div>
                </div>
            </div>
        )
    }

    renderDoneExercise(exercise, index, skipped) {
        let W = "";
        let R = "";
        let done = "";
        let note = "";
        if (exercise.hasOwnProperty('W')) {
            W = <div className="weight" key={index+"W"}>W:{exercise.W}</div>
        }
        if (exercise.hasOwnProperty('R')) {
            R = <div className="reps" key={index+"R"}>R:{exercise.R}</div>
        }
        if (exercise.hasOwnProperty('done')) {
            done = <div className="done" key={index+"D"}>{exercise.done ? "Done" : "Skip"}</div>
        }
        if (exercise.note !== "") {
            note = [<div className="exercise__noteBlock" key="noteBlock">Note</div>,
                <div className="exercise__note" key="note">{exercise.note}</div>];
        }
        let inputs =[W,R,done];

        return (
            <div className="exercise" key={index}>
                <div className="exercise__basic">
                    <div className="exercise__name">
                        {note}
                        {exercise.name}:
                    </div>
                    <div className="exercise__inputs">
                        {skipped ?  <div className="done">X</div> : inputs}
                    </div>
                </div>
            </div>
        )
    }

    renderWorkout(day, workout, index, weekN, firstUndone) {
        let content = [];
        let workoutClass = "workout";
        let _this = this;
        if (!workout.done) {
            let exercises = [];
            if (firstUndone) {
                workout.exercises.forEach(function (e, i) {
                    exercises.push(_this.renderExercise(e, i));
                });
                content.push(
                    <form className="workout__form" key="form">
                        {exercises}
                    </form>
                );
            } else {
                workout.exercises.forEach(function (e, i) {
                    exercises.push(_this.renderTodoExercise(e, i));
                });
                content.push(
                    <div className="workout__list" key="list">
                        {exercises}
                    </div>
                );
            }
            if (firstUndone) {
                workoutClass = "workout workout--first";
                content.push(
                    <button type="button" className="workout__send"
                            onClick={() => this.send(weekN, day, workout.time, "done")} key="send">
                        Send
                    </button>,
                    <button type="button" className="workout__skip"
                            onClick={() => this.send(weekN, day, workout.time, "skip")} key="skip">
                        Skip
                    </button>
                );
            } else {
                content.push(
                    <div className="workout__footer workout__footer--TODO" key="todo">You have other workouts to
                        do!</div>
                );
            }
        } else if (workout.done) {
            let exercises = [];
            workout.exercises.forEach(function (e, i) {
                exercises.push(_this.renderDoneExercise(e, i, workout.skipped));
            });
            content.push(
                <div className="workout__list" key="list">
                    {exercises}
                </div>);
            if (!workout.skipped) {
                content.push(<div className="workout__footer workout__footer--goodJob" key="done">It's done! Good
                    job!</div>)
            }
            else {
                content.push(<div className="workout__footer workout__footer--skipped" key="skipped">This workout has
                    been skipped!</div>)
            }
        }

        return (
            <div className={workoutClass} key={index}>
                <div className="workout__week">Week {weekN}</div>
                {workout.done && !workout.skipped ?
                    <div className="workout__sticker workout__sticker--done">Done</div> : "" }
                {workout.done && workout.skipped ?
                    <div className="workout__sticker workout__sticker--skipped">Skipped</div> : "" }
                {workoutClass === "workout workout--first" ?
                    <div className="workout__sticker workout__sticker--current">Current</div> : ""}
                <div className={"workout__background " + "workout__background--" + workout.time}></div>
                <div className="workout__infoBox">i</div>
                <div className="workout__description">{workout.description}</div>
                <div className={"workout__time " + "workout__time--" + workout.time }>{day + " - " + workout.time}</div>
                <div className="workout__name">{workout.name}</div>
                {content}
            </div>
        )
    }

    renderShortcutDayRadio(day, index) {
        return (
            <div className="shortcut__row" key={index}>
                <input type="radio" name="day" value={day} id={day}/>
                <label htmlFor={day}>{day}</label>
            </div>
        )
    }

    changeDesc() {
        let description = this.state.description;
        this.setState({description: !description});
    }

    render() {
        let weeks = [];
        let _this = this;
        let weekNumber = 0;
        let weekShortCuts = [];
        let firstUndone = true;

        this.state.sheet.weeks.forEach(function (week, week_i) {
            let workouts = [];
            weekNumber++;
            weekShortCuts.push(
                <div className="shortcut__row" key={weekNumber}>
                    <input type="radio" name="week" value={weekNumber} id={"week__" + weekNumber}/>
                    <label htmlFor={"week__" + weekNumber}>Week {weekNumber}</label>
                </div>
            );
            week.forEach(function (day, day_i) {
                day.workouts.forEach(function (workout, workout_i) {
                    workouts.push(
                        _this.renderWorkout(day.day, workout, day_i.toString() + "-" + workout_i.toString(), weekNumber, firstUndone)
                    );
                    if (firstUndone && !workout.done) {
                        firstUndone = false;
                    }
                });
            });
            weeks.push(
                <div className="week" key={week_i}>
                    <div className="week__name">{"Week " + weekNumber}</div>
                    {workouts}
                </div>);
        });

        let desc = (this.state.description) ? "" : "worksheet__description--closed";
        let days = ["Monday", "Thursday", "Wednesday", "Tuesday", "Friday", "Saturday", "Sunday"];
        let dayShortCuts = [];
        days.forEach(function (day, index) {
            dayShortCuts.push(
                _this.renderShortcutDayRadio(day, index)
            );
        });

        return (
            <div className="worksheet">
                <div className="worksheet__name">Your current worksheet: {this.state.sheet.name}</div>
                <div className="worksheet__info" onClick={() => this.changeDesc()}>Description</div>
                <div className={"worksheet__description " + desc}>
                    {this.state.sheet.description}
                    <div className="worksheet__description__close" onClick={() => this.changeDesc()}>
                        <span className="line line--1"/>
                        <span className="line line--2"/>
                    </div>
                </div>
                <div className="weeks">
                    {weeks}
                </div>
                <div className="arrow"></div>
                <div className="shortcut">
                    SHORTCUTS
                    <div className="shortcut__weeks">
                        {weekShortCuts}
                    </div>
                    <div className="shortcut__days">
                        {dayShortCuts}
                    </div>
                    <div className="shortcut__jump">
                        JUMP
                    </div>
                </div>
            </div>
        );
    }
}

export default Worksheet;
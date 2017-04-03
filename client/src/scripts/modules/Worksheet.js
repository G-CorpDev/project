import React, {Component} from 'react';

class Worksheet extends Component {
    constructor(props) {
        super(props);
        this.state = {
            test: require("../../json/test.json"),
            description: false,
        }
    }

    send() {
        console.log("sending data...");
    }

    renderExercise(exercise, index) {
        let W = "";
        if (exercise.hasOwnProperty('W')) {
            W = <input type="text" name="W" placeholder="W"></input>;
        }
        let R = "";
        if (exercise.hasOwnProperty('R')) {
            R = <input type="text" name="R" placeholder="R"></input>;
        }
        let done = "";
        if (exercise.hasOwnProperty('done')) {
            done = [<input type="checkbox" name="done" key="i"></input>,
                <label className="exercise__checkbox" key="l">
                    <div>L</div>
                </label>];
        }
        return (
            <div className="exercise" key={index}>
                <input type="checkbox" id="note" className="exercise__addNoteInput"></input>
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
                <input className="exercise__note" type="text" name="Note" placeholder="note"></input>
            </div>
        )
    }

    renderDoneExercise(exercise, index) {
        let W = "";
        if (exercise.hasOwnProperty('W')) {
            W = <div className="weight">W:{exercise.W}</div>;
        }
        let R = "";
        if (exercise.hasOwnProperty('R')) {
            R = <div className="reps">R:{exercise.R}</div>;
        }
        let done = "";
        if (exercise.hasOwnProperty('done')) {
            done = <div className="done">{exercise.done}</div>;
        }
        let note = "";
        if (exercise.note !== "") {
            note = <div className="exercise__note">{exercise.note}</div>;
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
                {note}
            </div>
        )
    }

    renderDay(day, workout, index, weekN) {
        let content = [];
        let _this = this;
        if (workout.done === "not") {
            let exercises = [];
            workout.exercises.forEach(function (e, i) {
                exercises.push(_this.renderExercise(e, i));
            });
            content.push(
                <form className="workout__form" key="form">
                    {exercises}
                </form>,
                <button type="button" className="workout__send" onClick={() => this.send()} key="send">
                    Send
                </button>
            );
        } else {
            let exercises = [];
            workout.exercises.forEach(function (e, i) {
                exercises.push(_this.renderDoneExercise(e, i));
            });
            content.push(
                <div className="workout__list" key="list">
                    {exercises}
                </div>
            )
        }

        return (
            <div className="workout" key={index}>
                <div className="workout__week">Week {weekN}</div>
                {workout.done !== "not" ? <div className="workout__sticker">Done</div> : "" }
                <div className={"workout__background " + "workout__background--" + workout.time}></div>
                <div className="workout__infoBox">i</div>
                <div className="workout__description">{workout.description}</div>
                <div className="workout__time">{day + " - " + workout.time}</div>
                <div className="workout__name">{workout.name}</div>
                {content}
            </div>
        )
    }

    calcMousePosRelToParent(event) {
        let bounds = event.target.getBoundingClientRect();
        let x = event.clientX - bounds.left;
        let y = event.clientY - bounds.top;
        console.log(' X Position: ' + x
            + ' Y Position: ' + y);
    }

    changeDesc() {
        let description = this.state.description;
        this.setState({description: !description});
    }

    render() {
        let weeks = [];
        let _this = this;
        let weekNumber = 0;

        this.state.test.weeks.forEach(function (week, week_i) {
            let workouts = [];
            weekNumber ++;
            week.forEach(function (day, day_i) {
                day.workouts.forEach(function (workout, workout_i) {
                    workouts.push(
                        _this.renderDay(day.day, workout, day_i.toString() + "-" + workout_i.toString(),weekNumber)
                    );
                });
            });
            weeks.push(<div className="week" key={week_i}>{workouts}</div>);
        });

        let desc = (this.state.description) ? "" : "worksheet__description--closed";

        return (
            <div className="worksheet">
                <div className="worksheet__name">Your current worksheet: {this.state.test.name}</div>
                <div className="worksheet__info" onClick={() => this.changeDesc()}>Description</div>
                <div className={"worksheet__description " + desc}>
                    {this.state.test.description}
                    <div className="worksheet__description__close" onClick={() => this.changeDesc()}>
                        <span className="line line--1"></span>
                        <span className="line line--2"></span>
                    </div>
                </div>
                {weeks}
            </div>
        );
    }
}

export default Worksheet;
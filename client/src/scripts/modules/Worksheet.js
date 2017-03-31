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
            W = <input type="text" name="W" placeholder="Weight"></input>;
        }
        return (
            <div className="exercise" key={index}>
                <div className="exercise__name">
                    <div className="exercise__addNote">Note</div>
                    {exercise.name}:
                </div>
                <div className="exercise__inputs">
                    {W}
                    <input type="text" name="R" placeholder="Reps"></input>
                </div>
            </div>
        )
    }

    renderDay(day, workout, index) {
        let exercises = [];
        let _this = this;
        workout.exercises.forEach(function (e, i) {
            exercises.push(_this.renderExercise(e, i));
        });

        return (
            <div className="workout" key={index}>
                <div className="workout__info">i</div>
                <div className="workout__description">{workout.description}</div>
                <div className="workout__day">{day + " - " + workout.time}</div>
                <div className="workout__name">{workout.name}</div>
                <form className="workout__form">
                    {exercises}
                </form>
                <button type="button" className="workout__send" onClick={() => this.send()}>
                    Send
                </button>
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
        console.log(this.state.test);

        this.state.test.weeks.forEach(function (week, week_i) {
            let workouts = [];
            week.forEach(function (day, day_i) {
                day.workouts.forEach(function (workout, workout_i) {
                    workouts.push(_this.renderDay(day.day, workout, day_i.toString() + "-" + workout_i.toString()));
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
import React, {Component} from 'react';
import axios from 'axios';

class Auth extends Component {
    constructor(props) {
        super(props);
        this.state = {
            logging: false,
            regInputs: ["Username", "Password", "Confirm password", "Nickname", "Sex", "Age", "Height", "Weight"],
            regValues: ["", "", "", "", "", "", "", ""],
            logInputs: ["Username", "Password"],
            logValues: ["", ""],
            flip: props.flip,
        }
    }

    login() {
        let logging = this.state.logging;
        this.setState({logging: !logging});
        if (!logging) {
            console.log("logging in...");
            axios.post('http://localhost:3000/login', {username: this.state.logInputs[0], password: this.state.logInputs[1]})
                .then(function (response) {
                    console.log("response: " + response);
                });
        }
    }

    register() {
        console.log("Making Registration...");
    }

    flip() {
        this.setState({logging: false});
        this.state.flip();
    }

    handleChange(index, g, event) {
        if (g === "register") {
            let regValues = this.state.regValues.slice();
            regValues[index] = event.target.value;
            this.setState({regValues: regValues});
        } else {
            let logValues = this.state.logValues.slice();
            logValues[index] = event.target.value;
            this.setState({logValues: logValues});
        }

    }

    renderInput(g, label, index) {
        let used = "";
        if (g === "register") {
            used = this.state.regValues[index] !== "" ? "used " : "";
        } else {
            used = this.state.logValues[index] !== "" ? "used " : "";
        }
        return (
            <div className={g + "__row"} key={index}>
                <input type="text" className={g + "__input " + used + label}
                       onChange={this.handleChange.bind(this, index, g)}/>
                <label>{label}</label>
            </div>
        )
    }

    render() {
        let regRows = [];
        let logRows = [];
        let _this = this;
        this.state.regInputs.forEach(function (element, index) {
            regRows.push(_this.renderInput("register", element, index));
        });
        this.state.logInputs.forEach(function (element, index) {
            logRows.push(_this.renderInput("login", element, index));
        });

        return (
            <div className="auth">
                <div className="register">
                    <div className="register__form">
                        {regRows}
                        <button type="button" className="submit" onClick={() => this.register()}>
                            Sign up
                        </button>
                        <p className="register__signin">Already have an account? &nbsp;<a onClick={() => this.flip()}>Sign
                            in</a></p>
                    </div>
                </div>
                <div className="login">
                    <div className="login__person">
                        <div
                            className={"login__person__head " + (this.state.logging ? "login__person__head--logging" : "")}></div>
                        <div className="login__person__body"></div>
                    </div>
                    <div className="login__form">
                        {logRows}
                        <button type="button" className="submit" onClick={() => this.login()}>
                            {this.state.logging ? "Logging in..." : "Sign in"}
                        </button>
                        <p className="login__signup">Don't have an account? &nbsp;<a onClick={() => this.flip()}>Sign
                            up</a></p>
                    </div>
                </div>
            </div>
        );
    }
}

export default Auth;

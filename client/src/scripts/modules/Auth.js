import React, {Component} from 'react';
import axios from 'axios';

class Auth extends Component {
    constructor(props) {
        super(props);
        this.state = {
            logging: false,
            regInputs: ["Username", "Password", "Confirm password", "Nickname"],
            regValues: ["", "", "", ""],
            logInputs: ["Username", "Password"],
            logValues: ["", ""],
            flip: props.flip,
            login: props.login,
        }
    }

    login() {
        let logging = this.state.logging;
        let _this = this;
        if (!logging) {
            this.setState({logging: true});
            console.log("logging in...");
            setTimeout(function () {

                //POSTING
                axios.post('http://localhost:3000/login', {
                    username: _this.state.logValues[0],
                    password: _this.state.logValues[1]
                })
                    .then(function (response) {
                        console.log(response);
                        _this.state.login(response.data.id, response.data.displayName);
                    }).catch(function (error) {
                    if (error.response) {
                        // The request was made, but the server responded with a status code
                        // that falls out of the range of 2xx
                        console.log(error.response.data);
                        let status = error.response.status;
                        console.log(status);
                        console.log(error.response.headers);
                        _this.setState({logging: false});
                        if (status === 401) {
                            window.alert("Error: " + status + ", wrong user data.")
                        } else {
                            window.alert("Error: " + status)
                        }
                    } else {
                        // Something happened in setting up the request that triggered an Error
                        console.log('Error: ', error.message);
                    }
                });

                //TESTING
                //_this.state.login("1","Bela");

            }, 1500);
        }
    }

    register() {
        let _this = this;

        if (this.state.regValues[1].toString() !== this.state.regValues[2].toString()) {
            window.alert("Use the same password, Fuckhead. ");
        } else {
            console.log("Making Registration...");
            axios.post('http://localhost:3000/register', {
                username: _this.state.regValues[0],
                password: _this.state.regValues[1],
                nickname: _this.state.regValues[3],
            })
                .then(function (response) {
                    console.log(response);
                    window.alert("Good job, Motherfucker. ");
                    _this.flip();
                }).catch(function (error) {
                if (error.response) {
                    console.log(error.response.data);
                    let status = error.response.status;
                    console.log(status);
                    console.log(error.response.headers);
                    this.setState({logging: false});
                    window.alert("Error: " + status);
                } else {
                    console.log('Error: ', error.message);
                }
            });
        }
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

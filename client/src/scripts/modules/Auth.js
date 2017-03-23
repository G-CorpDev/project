import React, {Component} from 'react';

class Auth extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div className="auth">
                <div className="login">
                    <div className="login__person">
                        <div className="login__person__head"></div>
                        <div className="login__person__body"></div>
                    </div>
                    <div className="login__form">
                        <div className="login__row">
                            <input type="text" className="login__input name" placeholder="Username"/>
                        </div>
                        <div className="login__row">
                            <input type="password" className="login__input pass" placeholder="Password"/>
                        </div>
                        <button type="button" className="login__submit">Sign in</button>
                        <p className="login__signup">Don't have an account? &nbsp;<a>Sign up</a></p>
                    </div>
                </div>
            </div>
        );
    }
}

export default Auth;
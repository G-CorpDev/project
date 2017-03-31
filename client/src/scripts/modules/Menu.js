import React, {Component} from 'react';

class Menu extends Component {
    constructor(props) {
        super(props);
        this.state = {
            login: props.login,
        }
    }

    render() {

        return (
            <div className="menu">
                <li>My profile</li>
                <li>Select new worksheet</li>
                <li>Create worksheet</li>
                <li>Body mass index calculator</li>
                <li>Calorie calculator</li>
                <li onClick={() => this.state.login()}>Logout</li>
            </div>
        );
    }
}

export default Menu;
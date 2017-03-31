import React, {Component} from 'react';

import Worksheet from './Worksheet.js';
import Menu from './Menu.js';

class Content extends Component {
    constructor(props) {
        super(props);
        this.state = {
            login: props.login,
        }
    }

    render() {

        return (
            <div className="content">
                <Menu login={() => this.state.login()}/>
                <Worksheet/>
            </div>
        );
    }
}

export default Content;
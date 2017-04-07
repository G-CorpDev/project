import React, {Component} from 'react';

import Worksheet from './Worksheet.js';
import SheetList from './SheetList.js';
import Menu from './Menu.js';

class Content extends Component {
    constructor(props) {
        super(props);
        this.state = {
            logout: props.logout,
            selectedContent: "Select new worksheet",
            nick: props.nick,
        }
    }

    selectContent (content) {
        this.setState({selectedContent:content});
    }

    render() {

        return (
            <div className="content">
                <Menu logout={() => this.state.logout()} select={(i) => this.selectContent(i)} nick={this.state.nick}/>
                {this.state.selectedContent === "My worksheet" ? <Worksheet/> : ""}
                {this.state.selectedContent === "Select new worksheet" ? <SheetList/> : ""}
            </div>
        );
    }
}

export default Content;
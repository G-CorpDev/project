import React, {Component} from 'react';

import Worksheet from './Worksheet.js';
import SheetList from './SheetList.js';
import Menu from './Menu.js';

class Content extends Component {
    constructor(props) {
        super(props);
        this.state = {
            logout: props.logout,
            selectedContent: "My worksheet",
            nick: props.nick,
            id: props.id,
        }
    }

    selectContent(content) {
        this.setState({selectedContent: content});
    }

    render() {

        return (
            <div className="content">
                <Menu logout={() => this.state.logout()} select={(i) => this.selectContent(i)} nick={this.state.nick}/>
                {this.state.selectedContent === "My worksheet" ? <Worksheet id={this.state.id}/> : ""}
                {this.state.selectedContent === "Select new worksheet" ? <SheetList id={this.state.id}/> : ""}
            </div>
        );
    }
}

export default Content;
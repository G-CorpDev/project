import React, {Component} from 'react';

import Worksheet from './Worksheet.js';
import SheetList from './SheetList.js';
import Menu from './Menu.js';

class Content extends Component {
    constructor(props) {
        super(props);
        this.state = {
            login: props.login,
            selectedContent: "Select new worksheet",
        }
    }

    selectContent (content) {
        this.setState({selectedContent:content});
    }

    render() {

        return (
            <div className="content">
                <Menu login={() => this.state.login()} select={(i) => this.selectContent(i)}/>
                {this.state.selectedContent === "My worksheet" ? <Worksheet/> : ""}
                {this.state.selectedContent === "Select new worksheet" ? <SheetList/> : ""}
            </div>
        );
    }
}

export default Content;
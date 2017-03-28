import React, {Component} from 'react';

import Auth from './Auth.js'

class Page extends Component {
    constructor(props) {
        super(props);
        this.state = {
            flip: "page--noflip"
        }
    }

    flip(){
        let flip = this.state.flip==="page--noflip" ? "page--flip" : "page--noflip";
        this.setState({flip: flip});
    }

    render() {
        return (
            <div className={"page " + this.state.flip}>
                <Auth flip={() => this.flip()}/>
            </div>
        );
    }
}

export default Page;
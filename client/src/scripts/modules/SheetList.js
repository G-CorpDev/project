import React, {Component} from 'react';

class SheetList extends Component {
    constructor(props) {
        super(props);
        this.state = {
            test: require("../../json/testList.json"),
        }
    }

    renderTableItem(item, index) {
        return (
            <tr className="item" key={index}>
                <th className="item__name">{item.name}</th>
                <th className="item__length">{item.length}</th>
                <th className="item__wLength">{item.avgWorkoutLength}</th>
                <th className={"item__difficulty " + "item__difficulty--" + item.difficulty}>{item.difficulty}</th>
                <th className="item__description">{item.description}</th>
                <th className="item__select">Select</th>
            </tr>
        )
    }

    render() {
        let _this = this;
        let sheets = [];
        this.state.test.sheets.forEach(function (item, index) {
            sheets.push(_this.renderTableItem(item, index));
        });
        let orderButtons = [<div className="asc" key="asc">▲</div>,<div className="desc" key="desc">▼</div>];

        return (
            <div className="sheetList">
                <table className="table">
                    <thead>
                        <tr className="table__header">
                            <th>Name{orderButtons}</th>
                            <th>Length{orderButtons}</th>
                            <th>Average workout time{orderButtons}</th>
                            <th>Difficulty{orderButtons}</th>
                            <th>Description</th>
                            <th>Select</th>
                        </tr>
                    </thead>
                    <tbody>
                        {sheets}
                    </tbody>
                </table>
            </div>
        );
    }
}

export default SheetList;
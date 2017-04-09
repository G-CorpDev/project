import React, {Component} from 'react';
import axios from 'axios';

class SheetList extends Component {
    constructor(props) {
        super(props);
        this.state = {
            sheetsJson: require("../../json/testList.json"),
        }
    }

    componentDidMount() {
        this.sortWorksheet("None", false);
    }

    sortWorksheet(orderAction, desc) {
        let _this = this;
        axios.post('http://localhost:3000/worksheets', {sortBy: orderAction, descending: desc})
            .then(function (response) {
                console.log(response);
                _this.setState({sheetsJson: response.data});
            })
            .catch(function (error) {
                console.log(error);
                window.alert(error);
            });
    }

    selectNewSheet(name) {
        let _this = this;
        axios.post('http://localhost:3000/users/:' + _this.state.id + '/SelectWorksheet ',
            {worksheet: name})
            .then(function (response) {
                console.log(response);
                window.alert("Worksheet selected");
            })
            .catch(function (error) {
                console.log(error);
                window.alert(error);
            });
    }

    renderTableItem(item, index) {
        return (
            <tr className="item" key={index}>
                <th className="item__name">{item.name}</th>
                <th className="item__length">{item.length}</th>
                <th className="item__wTime">{item.avgWorkoutTime}</th>
                <th className={"item__difficulty " + "item__difficulty--" + item.difficulty}>{item.difficulty}</th>
                <th className="item__description">{item.description}</th>
                <th className="item__select" onClick={() => this.selectNewSheet(item.name)}>Select</th>
            </tr>
        )
    }

    renderTableHeader(name, index) {
        let orderAction = name;
        if (name === "Average workout time") {
            orderAction = "AvgWorkoutTime"
        }
        let orderButtons = [
            <div className="asc" key="asc" onClick={() => this.sortWorksheet(orderAction, false)}>▲</div>,
            <div className="desc" key="desc" onClick={() => this.sortWorksheet(orderAction, true)}>▼</div>
        ];
        return (
            <th key={index}>{name}{orderButtons}</th>
        )
    }

    render() {
        let _this = this;
        let sheets = [];
        this.state.sheetsJson.sheets.forEach(function (item, index) {
            sheets.push(_this.renderTableItem(item, index));
        });

        let columns = ["Name", "Length", "Average workout time", "Difficulty"];
        let headers = [];
        columns.forEach(function (item, index) {
            headers.push(_this.renderTableHeader(item, index));
        });

        return (
            <div className="sheetList">
                <table className="table">
                    <thead>
                    <tr className="table__header">
                        {headers}
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
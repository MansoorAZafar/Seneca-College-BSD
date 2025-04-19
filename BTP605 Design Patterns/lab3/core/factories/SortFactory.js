import {SelectionSortStrategy} from "../strategies/SelectionSortStrategy.js";
import {InsertionSortStrategy} from "../strategies/InsertionSortStrategy.js";
import {QuickSortStrategy} from "../strategies/QuickSortStrategy.js";

class SortFactory {
    static instance = null;

    constructor() {
        if(!SortFactory.instance) {
            alert('made a new one')
            SortFactory.instance = this;
        } else {
            alert('did not make a new one')
        }
        return SortFactory.instance;
    }

    GetInstance(type) {
        switch(type.toLowerCase()) {
            case "ssort":
                return new SelectionSortStrategy();
            case "isort":
                return new InsertionSortStrategy();
            default:
                return new QuickSortStrategy();
        }
    }
}

export {SortFactory};
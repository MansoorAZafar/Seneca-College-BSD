import { SortStrategy } from "../../models/interfaces/SortStrategy.js";

class InsertionSortStrategy extends SortStrategy {
    *sort(arr) {
        for(let i = 1; i < arr.length; ++i) {
            let key = arr[i];
            let j = i - 1;

            while(arr[j] > key && j >= 0) {
                arr[j + 1] = arr[j];
                j -= 1;
            }
            arr[j + 1] = key;

            yield arr.slice();
        }
    }
}

export {InsertionSortStrategy};
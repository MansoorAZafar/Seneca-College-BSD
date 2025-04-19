
import { SortStrategy } from "../../models/interfaces/SortStrategy.js";

class QuickSortStrategy extends SortStrategy {
    *sort(arr, left=0, right=arr.length - 1) {
        if(left < right) {
            let pivot = this.partition(arr, left, right);
            yield arr.slice(); // return ish the current values

            yield* this.sort(arr, left, pivot - 1);
            yield* this.sort(arr, pivot + 1, right);
        }
    }

    partition(arr, left, right) {
        let pivot = arr[right];
        let i = left - 1;

        for(let j = left; j < right; ++j) {
            if(arr[j] < pivot) {
                ++i;
                [arr[j], arr[i]] = [arr[i], arr[j]];
            }
        }
        [arr[i+1], arr[right]] = [arr[right], arr[i + 1]];
        return i+1;
    }
}

export {QuickSortStrategy};
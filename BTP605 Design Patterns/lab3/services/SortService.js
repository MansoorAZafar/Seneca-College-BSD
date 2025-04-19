class SortService {
    constructor() {
        this.strategy = null;
        this.sortingPaused = false
        this.sortingDone = false
        this.sortingStep = null;
    }

    setService(strategy) {
        this.strategy = strategy;
    }

    startAnimation(arr) {
        if(this.sortingPaused) return;

        if(this.sortingStep == null) {
            this.sortingStep = this.strategy.sort(arr);
        }

        if(this.sortingDone) {
            this.sortingDone = false;
            this.sortingStep = this.strategy.sort(arr);
        }

        clearInterval(this.sortingInterval); // stop any previous animations
        this.sortingInterval = setInterval(() => {
            if(!this.sortingDone) {
                let step = this.sortingStep.next();
                if(step.done) {
                    this.sortingDone = true;
                    clearInterval(this.sortingInterval);
                }
            }
        }, 50)
    }

    pause() {
        alert(`Paused: ${!this.sortingPaused}`);
        this.sortingPaused = !this.sortingPaused;
    }
}

export {SortService};
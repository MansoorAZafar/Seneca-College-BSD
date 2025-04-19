import { SortType } from "./models/SortType.js";
import { SortFactory } from "./core/factories/SortFactory.js";
import { SortService } from "./services/SortService.js";


let values = [];
let barWidth = 5;
const maxValues = 65;
const scaleFactor = 7;
const sortFactory = new SortFactory();
let sorter;


// Randomize array values
function randomizeValues() {
    values = [];
    for (let i = 0; i < maxValues; ++i) {
        values[i] = Math.floor(Math.random() * 20 + 10);
    }
}

// Start sorting animation
function sortValues(type) {
    sorter.setService(sortFactory.GetInstance(type));
    sorter.startAnimation(values);
}

// Pause or Resume Sorting
function togglePause() {
    sorter.pause();
}

new p5((p) => {

    p.setup = function() {
        p.createCanvas(1200, 500);
        randomizeValues();
    
        let quickSortButton = p.createButton("Quick Sort");
        quickSortButton.mousePressed(() => sortValues(SortType['Quick Sort']));
        quickSortButton.position(20, 20);

        let selectionSortButton = p.createButton("Selection Sort");
        selectionSortButton.mousePressed(() => sortValues(SortType['Selection Sort']));
        selectionSortButton.position(120, 20);

        let insertionSortButton = p.createButton("Insertion Sort");
        insertionSortButton.mousePressed(() => sortValues(SortType['Insertion Sort']));
        insertionSortButton.position(220, 20);
    
        let randomizeButton = p.createButton("Randomize");
        randomizeButton.mousePressed(randomizeValues);
        randomizeButton.position(320, 20);
    
        let pauseButton = p.createButton("Pause/Play");
        pauseButton.mousePressed(togglePause);
        pauseButton.position(420, 20);

        new SortFactory(); // the next one should say "did not make a new one"
        
        sorter = new SortService();
    }
    
    p.draw = function() {
        p.background(255, 255, 255);
        
        // Draw bars
        for (let i = 0; i < maxValues; i++) {
            p.fill(0, 0, 0);
            p.rect(50 + i * (barWidth + 10), p.height - (values[i] * scaleFactor), barWidth, values[i] * scaleFactor);
        }
    }
});

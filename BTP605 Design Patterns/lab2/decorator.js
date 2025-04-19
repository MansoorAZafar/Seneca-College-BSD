var Label = function(labelText,x,y){
	var that = {};
	var labelText_=labelText || "";
	var x_=x || 200;
	var y_=y || 200;
	var width_ = labelText_.length * 10;
	var height_ = 40;

	that.draw = function(){
		strokeWeight(1);
		stroke(0,0,0);
		fill(0,0,0);
		textAlign(CENTER,CENTER);
		text(labelText_,x_,y_);
	}

	that.getX = function() {
		return x_;
	}	
	that.getY = function() {
		return y_;
	}
	that.getWidth = function() {
		return width_;
	}
	that.getHeight = function() {
		return height_;
	}

	that.addHeight = function(height) {
		height_ += height
	}

	that.addWidth = function(width) {
		width_ += width
	}

	return that;
};

var labels=[];
var thickBorderButton;
var borderButton;
var dotButton;
var removeButton;
var selectLabelRadio;
var selected;
var numLabels;

/*
  these four functions are called when button is pressed
  modify the "add" functions to apply decorator to the 
  selected label.   
*/

function addThinBorder(){
	var label = labels[selected];
	const height = label.getHeight();
	const width = label.getWidth();

	var drawPreviousState = label.draw
	label.draw = function() {
		drawPreviousState();

		rectMode(CENTER);
		strokeWeight(1);
		stroke(0,0,0);
		noFill();
		rect(label.getX(),label.getY(),width,height);				
	}
	
	label.addHeight(8);
	label.addWidth(8);
}

function addThick(){
	
	var label = labels[selected];
	const height = label.getHeight();
	const width = label.getWidth();

	var drawPreviousState = label.draw
	label.draw = function() {
		drawPreviousState();

		rectMode(CENTER);
		strokeWeight(3);
		stroke(0,0,0);
		noFill();
		rect(label.getX(),label.getY(),width,height);	
	}
	
	label.addHeight(13);
	label.addWidth(13);

}
function addDots(){
	var label = labels[selected];
	const height = label.getHeight();
	const width = label.getWidth();
	
	var drawPreviousState = label.draw
	label.draw = function() {
		drawPreviousState();

		ellipseMode(CENTER);
		strokeWeight(1);
		fill(255,0,0);
		stroke(255,0,0);
		//above label
		for(var i=0;i<width/10 + 1;i++){
			ellipse((label.getX()-width/2+i*10),(label.getY()-height/2),5,5);
		}
		//below label
		for(var i=0;i<width/10 +1;i++){
			ellipse((label.getX()-width/2+i*10),(label.getY()+height/2),5,5);
		}
		//left of label
		for(var i=0;i<height/10-1;i++){
			ellipse((label.getX()-width/2),(label.getY()-height/2+((i+1)*10)),5,5);
		}
		//right of label
		for(var i=0;i<height/10-1;i++){
			ellipse((label.getX()+width/2),(label.getY()-height/2+((i+1)*10)),5,5);
		}			
	}	
		
	label.addHeight(18);
	label.addWidth(18);
}

function addCustomBorder() {
	var label = labels[selected];
	const width = label.getWidth();

	var drawPreviousState = label.draw
	label.draw = function() {
		drawPreviousState();
		rectMode(CENTER);
		strokeWeight(3);
		stroke(0,0,0);
		noFill();
		circle(label.getX(),label.getY(),width);	
	}
	
	label.addHeight(15*2+15);
	label.addWidth(15*2+15);
}

/*
  Challenge: removeLastBorder function.  If you add this feature
  use this function to remove the most recent decorator 
  from the selected label
 */
function removeLastBorder(){
}


/*********************************************************/
/* NOTHING BELOW THIS COMMENT IS TO BE MODIFIED          */
/*********************************************************/

function setup(){
	createCanvas(600,500);	

    thickBorderButton=createButton("Add Thick Border");
    thickBorderButton.mousePressed(addThick);
    thickBorderButton.position(10,550);
    borderButton=createButton("Add Thin Border");
    borderButton.mousePressed(addThinBorder);
    borderButton.position(160,550);
    dotButton=createButton("Add Dots Border");
    dotButton.mousePressed(addDots);
    dotButton.position(310,550);

    removeButton=createButton("Remove Last");
    removeButton.mousePressed(removeLastBorder);
    removeButton.position(460,550);
	//Custom Button Lines [179-182]
	customButton=createButton("Custom Shape Button");
	customButton.mousePressed(addCustomBorder);
	customButton.position(510, 660);
	
	selectLabelRadio=createRadio();
	numLabels=5;
	for(var i=0;i<numLabels;i++){
		selectLabelRadio.option(""+i,"Label "+(i+1));
		labels[i] = Label("Label "+(i+1), random(50,550), random(20,480));
	}
    selectLabelRadio.selected(0);

}


/* This function is not to be modified*/
function draw(){
	selected=selectLabelRadio.value();
	background(255,255,255);
	for(var i=0;i<numLabels;i++){
		labels[i].draw();
	}
}
	

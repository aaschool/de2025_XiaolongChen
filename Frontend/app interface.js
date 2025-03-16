
// Global variables for physiological data and mode selection
let stressLevel = 0;
let heartRate = 0;
let lastUpdate = 0;
let mode = "Relaxation"; // default mode
let modeSelect;

function setup() {
  createCanvas(windowWidth, windowHeight);
  background(255);

  // Create a mode selection dropdown
  modeSelect = createSelect();
  modeSelect.position(20, 20);
  modeSelect.option("Relaxation");
  modeSelect.option("Focus");
  modeSelect.option("Meditation");
  modeSelect.changed(changeMode);

  // Create a button to manually fetch data
  let fetchButton = createButton("Fetch Data");
  fetchButton.position(20, 60);
  fetchButton.mousePressed(fetchData);

  // Automatically fetch data every 5 seconds
  setInterval(fetchData, 5000);

  // Initial data fetch
  fetchData();
}

function draw() {
  background(255);

  // Display current mode and physiological data
  fill(0);
  textSize(18);
  textAlign(LEFT, TOP);
  text("Mode: " + mode, 20, 100);
  text("Stress Level: " + stressLevel, 20, 130);
  text("Heart Rate: " + heartRate, 20, 160);
  text("Last Update: " + new Date(lastUpdate).toLocaleTimeString(), 20, 190);

  // Dynamic visual feedback based on stress level
  let dynamicSize = map(stressLevel, 0, 100, 50, 300);
  let dynamicColor = lerpColor(color(0, 255, 0), color(255, 0, 0), stressLevel / 100);
  fill(dynamicColor);
  noStroke();
  ellipse(width / 2, height / 2, dynamicSize, dynamicSize);

  // Additional visual effects based on selected mode
  if (mode === "Relaxation") {
    // Calm visual effect: overlay a semi-transparent circle
    fill(0, 150);
    ellipse(width / 2, height / 2, dynamicSize * 0.8, dynamicSize * 0.8);
  } else if (mode === "Focus") {
    // Focus visual effect: draw a sharp rectangle
    stroke(0);
    strokeWeight(2);
    noFill();
    rectMode(CENTER);
    rect(width / 2, height / 2, dynamicSize, dynamicSize);
  } else if (mode === "Meditation") {
    // Meditation visual effect: draw a soothing spiral
    push();
    translate(width / 2, height / 2);
    stroke(0, 100);
    noFill();
    beginShape();
    for (let angle = 0; angle < TWO_PI * 3; angle += 0.1) {
      let r = map(angle, 0, TWO_PI * 3, 0, dynamicSize);
      let x = r * cos(angle);
      let y = r * sin(angle);
      vertex(x, y);
    }
    endShape();
    pop();
  }
}

// Fetch data from the backend at the '/data' endpoint
function fetchData() {
  fetch('/data')
    .then(response => response.json())
    .then(data => {
      // Assuming the backend returns an object with stressLevel and heartRate properties
      stressLevel = data.stressLevel;
      heartRate = data.heartRate;
      lastUpdate = Date.now();
      console.log("Data fetched:", data);
    })
    .catch(error => {
      console.error("Error fetching data:", error);
    });
}

// Change the current mode when the dropdown value changes
function changeMode() {
  mode = modeSelect.value();
  console.log("Mode changed to:", mode);
}

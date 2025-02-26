let espIp = "192.168.1.100"; // <-- Replace with your ESP8266 IP
let heartRate = 0;
let stressLevel = "";
let breathingRate = 0;
let sessionActive = false;

// UI elements
let heartRateP, stressLevelP, breathingRateP, sessionStatusP;
let startBtn, endBtn;

function setup() {
  noCanvas(); // We'll use p5.dom for UI, not drawing on canvas

  createElement("h2", "Current Session Status").parent("app");

  sessionStatusP = createP("Session: Inactive").parent("app");
  heartRateP = createP("Heart Rate: -- BPM").parent("app");
  stressLevelP = createP("Stress Level: --").parent("app");
  breathingRateP = createP("Breathing Rate: -- BPM").parent("app");

  // Buttons
  startBtn = createButton("Start Session").parent("app");
  startBtn.mousePressed(startSession);

  endBtn = createButton("End Session").parent("app");
  endBtn.mousePressed(endSession);

  // Fetch data every 3 seconds
  setInterval(fetchDataFromESP, 3000);
}

function fetchDataFromESP() {
  fetch(`http://${espIp}/data`)
    .then(response => response.json())
    .then(data => {
      heartRate = data.heartRate;
      stressLevel = data.stressLevel;
      breathingRate = data.breathingRate;
      sessionActive = data.sessionActive;
      updateUI();
    })
    .catch(err => {
      console.error("Error fetching data:", err);
    });
}

function updateUI() {
  sessionStatusP.html(`Session: ${sessionActive ? "Active" : "Inactive"}`);
  heartRateP.html(`Heart Rate: ${heartRate} BPM`);
  stressLevelP.html(`Stress Level: ${stressLevel}`);
  breathingRateP.html(`Breathing Rate: ${breathingRate} BPM`);
}

function startSession() {
  fetch(`http://${espIp}/startSession`)
    .then(response => response.text())
    .then(msg => console.log("ESP Response:", msg))
    .catch(err => console.error("Error starting session:", err));
}

function endSession() {
  fetch(`http://${espIp}/endSession`)
    .then(response => response.text())
    .then(msg => console.log("ESP Response:", msg))
    .catch(err => console.error("Error ending session:", err));
}

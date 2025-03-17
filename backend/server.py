# server.py

from flask import Flask, jsonify, request
import random
import time

app = Flask(__name__)

def generate_physiological_data():
    """
    Simulate physiological data for demonstration purposes.
    Returns a dictionary with:
      - stressLevel: 0-100
      - heartRate: 60-100
      - breathingRate: 12-18
      - timestamp: current UNIX time
    """
    data = {
        "stressLevel": random.randint(0, 100),
        "heartRate": random.randint(60, 100),
        "breathingRate": random.randint(12, 18),
        "timestamp": int(time.time())
    }
    return data

@app.route('/data', methods=['GET'])
def get_data():
    """
    GET endpoint to retrieve simulated physiological data.
    In a real scenario, this might fetch data from Apple Watch or a database.
    """
    data = generate_physiological_data()
    return jsonify(data)

@app.route('/command', methods=['POST'])
def post_command():
    """
    POST endpoint to receive commands from the frontend or other clients.
    Expects a JSON payload with fields like "command" and "params".
    """
    command_data = request.get_json()
    if not command_data:
        return jsonify({"error": "No JSON payload received"}), 400

    command = command_data.get("command", "unknown")
    params = command_data.get("params", {})

    # Example: Log the command to the console (or perform actual hardware interactions)
    print(f"Received command: {command}, params: {params}")

    # Return a success response with the received data
    return jsonify({
        "status": "Command received",
        "command": command,
        "params": params
    }), 200

@app.route('/session', methods=['POST'])
def start_session():
    """
    Example endpoint to handle starting a meditation session.
    You could track session info in a database or call hardware control modules.
    """
    session_data = request.get_json()
    if not session_data:
        return jsonify({"error": "No session data received"}), 400

    session_id = random.randint(1000, 9999)  # Generate a mock session ID
    print(f"Starting session with data: {session_data}, assigned session ID: {session_id}")

    return jsonify({
        "status": "Session started",
        "sessionId": session_id,
        "sessionData": session_data
    }), 200

if __name__ == '__main__':
    # For production, consider using a proper WSGI server (e.g., gunicorn or uwsgi).
    app.run(debug=True, port=5000)

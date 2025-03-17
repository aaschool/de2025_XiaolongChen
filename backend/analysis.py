"""
analysis.py
-----------
Data processing and analysis logic for handling physiological data
(e.g., heart rate, stress level, breathing rate).

Example usage:
    from analysis import analyze_data
    
    data = {
        "heartRate": 85,
        "stressLevel": 50,
        "breathingRate": 15,
        "timestamp": 1679053420
    }
    results = analyze_data(data)
    print(results)
"""

def analyze_data(data):
    """
    Analyze physiological data to determine the user's current status.

    :param data: dict containing:
        - heartRate (int)
        - stressLevel (int)
        - breathingRate (int)
        - timestamp (int, optional)
    :return: dict with analysis results, including recommended mode.
    """

    # Extract values (with some defaulting in case keys are missing)
    heart_rate = data.get("heartRate", 70)
    stress_level = data.get("stressLevel", 30)
    breathing_rate = data.get("breathingRate", 15)

    # Initialize a results dictionary
    analysis_results = {
        "heartRateStatus": "Normal",
        "stressStatus": "Low",
        "breathingStatus": "Normal",
        "recommendedMode": "Light Meditation"
    }

    # Determine heart rate status
    if heart_rate < 60:
        analysis_results["heartRateStatus"] = "Below Normal"
    elif heart_rate > 90:
        analysis_results["heartRateStatus"] = "Elevated"

    # Determine stress status
    if stress_level > 60:
        analysis_results["stressStatus"] = "High"
    elif stress_level > 30:
        analysis_results["stressStatus"] = "Moderate"

    # Determine breathing status
    if breathing_rate < 12:
        analysis_results["breathingStatus"] = "Below Normal"
    elif breathing_rate > 18:
        analysis_results["breathingStatus"] = "Above Normal"

    # Recommend mode based on stress status
    if analysis_results["stressStatus"] == "High":
        analysis_results["recommendedMode"] = "Deep Relaxation"
    elif analysis_results["stressStatus"] == "Moderate":
        analysis_results["recommendedMode"] = "Focus Restoration"
    else:
        analysis_results["recommendedMode"] = "Light Meditation"

    return analysis_results

if __name__ == "__main__":
    # Example test run
    sample_data = {
        "heartRate": 92,
        "stressLevel": 70,
        "breathingRate": 19,
        "timestamp": 1679053420
    }
    print(analyze_data(sample_data))

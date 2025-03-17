def setup_dynamic_visuals():
    """
    Creates a basic operator network for dynamic visual effects.
    This network includes:
      - A Container COMP named "DynamicVisuals"
      - A Constant TOP for base color
      - A Noise TOP for generating dynamic patterns
      - A Feedback TOP to add feedback effects
      - A Composite TOP to blend the Noise and Feedback TOPs
      - An Out TOP to output the final composite image
    """
    root = op('/')  # Get the root operator (usually /project1)
    
    # Create a Container COMP called "DynamicVisuals" if it doesn't exist
    if not root.op('DynamicVisuals'):
        dynamicContainer = root.create('container', 'DynamicVisuals')
        dynamicContainer.par.w = 800
        dynamicContainer.par.h = 600
    else:
        dynamicContainer = root.op('DynamicVisuals')
    
    # Create a Constant TOP as the base layer
    if not dynamicContainer.op('Constant1'):
        constantTOP = dynamicContainer.create('constant', 'Constant1')
        constantTOP.par.color = [0.1, 0.1, 0.1, 1]  # Dark grey background
    else:
        constantTOP = dynamicContainer.op('Constant1')
    
    # Create a Noise TOP for generating dynamic patterns
    if not dynamicContainer.op('Noise1'):
        noiseTOP = dynamicContainer.create('noise', 'Noise1')
        noiseTOP.par.amplitude = 0.5
        noiseTOP.par.frequency = 0.8
    else:
        noiseTOP = dynamicContainer.op('Noise1')
    
    # Create a Feedback TOP for adding feedback effects
    if not dynamicContainer.op('Feedback1'):
        feedbackTOP = dynamicContainer.create('feedback', 'Feedback1')
    else:
        feedbackTOP = dynamicContainer.op('Feedback1')
    
    # Create a Composite TOP to blend the Noise and Feedback TOPs
    if not dynamicContainer.op('Composite1'):
        compositeTOP = dynamicContainer.create('composite', 'Composite1')
        # Connect Noise1 to input 0 and Feedback1 to input 1 of Composite1
        compositeTOP.inputConnectors[0].connect(noiseTOP)
        compositeTOP.inputConnectors[1].connect(feedbackTOP)
    else:
        compositeTOP = dynamicContainer.op('Composite1')
    
    # Create an Out TOP to output the final composite image
    if not dynamicContainer.op('Out1'):
        outTOP = dynamicContainer.create('out', 'Out1')
        outTOP.inputConnectors[0].connect(compositeTOP)
    else:
        outTOP = dynamicContainer.op('Out1')
    
    # Optionally, you can adjust parameters or add more TOPs here for further customization
    return dynamicContainer

# Execute the setup function to build the network
setup_dynamic_visuals()

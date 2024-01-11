import pyzenbo
import openai
import zhconv
import cv2
import spacy
import speech_recognition as sr
from pyzenbo.modules.dialog_system import RobotFace
from pyzenbo.modules.motion import Motion
from pyzenbo.modules.line_follower import LineFollowerConfig
from pyzenbo.modules.sensor import Sensor

#https://zenbo.asus.com/tw/developer/documents/zenbo_junior/Zenbo-Junior-Python-SDK/1.0.46/motion

nlp = spacy.load("zh_core_web_sm")
recognizer = sr.Recognizer()
host = '172.20.10.4'
#host = '192.168.0.38'
openai.api_key = ''
conversation_history = []

def facial_recognition():
    # Load the cascade
    try:
        face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
    except Exception as e:
        print(f"Loading failed, an error occurred: {str(e)}")
        return

    # To capture video from webcam. 
    cap = cv2.VideoCapture(0)

    while True:
        # try to read the frame
        try:
            _, img = cap.read()# _ is a throwaway variable
        except Exception as e:
            print(f"Reading failed, an error occurred: {str(e)}")
            return

        # Convert to grayscale
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        faces = face_cascade.detectMultiScale(gray, 1.1, 4)
        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        cv2.imshow('img', img)

        # Stop if escape key is pressed
        k = cv2.waitKey(16) & 0xff # About 60 fps
        if k==27:
            break
    cap.release()

def speech_recognition():
    # Initialize recognizer class (for recognizing the speech)
    r = sr.Recognizer()

    with sr.Microphone() as source:
        print("Talk")
        try:
            audio_text = r.listen(source, timeout = 5, phrase_time_limit = 60)
            user_input = r.recognize_google(audio_text)
            print("Don't worry, take your time before asking me")
        except sr.WaitTimeoutError:
            print("No speech input before timeout")
            return
    try:
        # using google speech recognition
        print("Text: " + user_input)
    except:
        print("Sorry, I did not get that")
        return

    # We have the user input, generate a response using GPT?
    openai.api_key = 'api-key'
    response = openai.Completion.create(
        engine = "text-davinci-003",
        prompt = user_input,
        temperature = 0.5,
        max_tokens = 1024
    )

    zenbo_response = response.choices[0].text.strip()
    print("Zenbo: " + zenbo_response)

    sdk.robot.speak(zenbo_response)

from summarizer import Summarizer
'''
pip install bert-extractive-summarizer
pip install transformers
pip install spacy
python -m spacy download en_core_web_sm
'''

def summarize_text(text : str):
    model = Summarizer()
    return model(text)


try:
    sdk = pyzenbo.connect(host)
except pyzenbo.PyZenboError as e:
    print(f"Error connecting to Zenbo: {e}")
    exit()

def process_user_input(prompt):
    global conversation_history
    conversation_history.append(prompt)

    try:
        facial_recognition()  # Integrate facial recognition
        sdk.robot.set_expression(RobotFace.PLEASED)
        response = get_openai_response(prompt)
        reply = zhconv.convert(response, 'zh-hant')
        sdk.robot.speak("我的回答是：" + reply)
        print("我的答案是:" + reply)
        conversation_history.append(reply)
        
        # Integrate speech recognition
        user_input = speech_recognition()
        if user_input:
            summary = summarize_text(user_input)
            sdk.robot.speak("你說的內容總結為：" + summary)
            conversation_history.append(summary)
        
        sdk.robot.speak("你還有什麼想問的嗎？")
    except pyzenbo.PyZenboError as e:
        print(f"與 Zenbo 通信時出錯: {e}")

def get_openai_response(prompt):
    prompt_with_history = " ".join(conversation_history + [prompt])
    try:
        response = openai.Completion.create(
            engine = 'text-davinci-003',
            prompt = (prompt_with_history + "答案不要太冗長"),
            temperature = 0.5,
            max_tokens = 1024,
            n = 1,
            stop = None,
        )
        return response.choices[0].text.strip()
    except openai.error.OpenAIError as e:
        print(f"OpenAI API error: {e}")
        return "Unable to generate response"
    

def display_camera_feed():
    try:
        # Set Zenbo's expression to indicate it's processing
        sdk.robot.set_expression(RobotFace.PROCESSING)
        
        # Capture an image from the camera
        image = sdk.robot.get_image()

        # Display the image using OpenCV
        cv2.imshow('Zenbo Camera Feed', image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

        # Reset Zenbo's expression
        sdk.robot.set_expression(RobotFace.DEFAULT)
    except pyzenbo.PyZenboError as e:
        print(f"Communication with Zenbo failed: {e}")

if __name__ == "__main__":
    
    sdk.robot.set_expression(RobotFace.PLEASED, "你想要問什麼問題？")
    prompt = input("你的問題: ")

    while prompt.lower() != "exit" and prompt.strip() != "":
        process_user_input(prompt)
        prompt = input("你的問題: ")

    sdk.robot.set_expression(RobotFace.HIDEFACE)
    sdk.release()
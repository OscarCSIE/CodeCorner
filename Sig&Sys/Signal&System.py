import pygame
import random
import os

SCREEN_WIDTH = 1024
SCREEN_HEIGHT = 768

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (128, 128, 128)

# Get the current directory and assets directory path
current_dir = os.path.dirname(os.path.abspath(__file__))
assets_dir = os.path.join(current_dir, "Assets")

background_images = []
for i in range(1, 12):
    background_image = pygame.image.load(os.path.join(assets_dir, f"background{i}.jpg"))
    background_image = pygame.transform.scale(background_image, (SCREEN_WIDTH, SCREEN_HEIGHT))
    background_images.append(background_image)

# Question Data
questions = [
    {
        'question': 'Question 1: What do you value most in life?',
        'answers': [
            'Strength and power', 
            'Knowledge and wisdom', 
            'Faith and devotion', 
            'Harmony with nature'
        ],
    },
    {
        'question': 'Question 2: What is your preferred way to solve conflicts?',
        'answers': [
            'Direct confrontation', 
            'Strategic planning and cunning', 
            'Using magical abilities', 
            'Persuasion and diplomacy'
        ],
    },
    {
        'question': 'Question 3: Which environment do you feel most at home in?',
        'answers': [
            'In the heart of a battle', 
            'In a library or study', 
            'In a sacred temple', 
            'In the wilderness'
        ],
    },
    {
        'question': 'Question 4: What kind of weapon would you choose in a fight?',
        'answers': [
            'A great axe', 
            'A spell book or wand', 
            'A holy symbol or mace', 
            'A bow or crossbow'
        ],
    },
    {
        'question': 'Question 5: How do you prefer to spend your free time?',
        'answers': [
            'Training and honing physical skills', 
            'Reading and studying new spells', 
            'Meditating or praying', 
            'Exploring nature'
        ],
    },
    {
        'question': 'Question 6: What is your approach to teamwork?',
        'answers': [
            'Lead the charge and inspire others', 
            'Support and heal your allies', 
            'Provide strategic advantages and sneak attacks', 
            'Use spells to control the battlefield'
        ],
    },
    {
        'question': 'Question 7: What motivates you the most?',
        'answers': [
            'A desire for adventure and discovery', 
            'The pursuit of knowledge and mastery', 
            'A commitment to a higher cause', 
            'The thrill of battle'
        ],
    },
    {
        'question': 'Question 8: Which of these skills do you excel in?',
        'answers': [
            'Hand-to-hand combat', 
            'Playing musical instruments', 
            'Crafting and using magic items', 
            'Tracking and survival'
        ],
    },
    {
        'question': 'Question 9: How would you describe your personality?',
        'answers': [
            'Bold and brash', 
            'Intelligent and curious', 
            'Devout and righteous', 
            'Mysterious and cunning'
        ],
    },
    {
        'question': 'Question 10: What kind of story do you see yourself in?',
        'answers': [
            'A tale of epic battles and heroism', 
            'A mystical journey of magic and discovery', 
            'A sacred quest to vanquish evil', 
            'An adventure in the untamed wilds'
        ],
    }
]
# Answer Mapping for Class Determination
answer_mapping = {
        'Strength and power': 'Barbarian',
        'Knowledge and wisdom': 'Wizard',
        'Faith and devotion': 'Cleric',
        'Harmony with nature': 'Druid',
        'Direct confrontation': 'Fighter',
        'Strategic planning and cunning': 'Rogue',
        'Using magical abilities': 'Sorcerer',
        'Persuasion and diplomacy': 'Bard',
        'In the heart of a battle': 'Barbarian',
        'In a library or study': 'Wizard',
        'In a sacred temple': 'Cleric',
        'In the wilderness': 'Ranger',
        'A great axe': 'Barbarian',
        'A spell book or wand': 'Wizard',
        'A holy symbol or mace': 'Cleric',
        'A bow or crossbow': 'Ranger',
        'Training and honing physical skills': 'Fighter',
        'Reading and studying new spells': 'Wizard',
        'Meditating or praying': 'Cleric',
        'Exploring nature': 'Druid',
        'Lead the charge and inspire others': 'Paladin',
        'Support and heal your allies': 'Cleric',
        'Provide strategic advantages and sneak attacks': 'Rogue',
        'Use spells to control the battlefield': 'Wizard',
        'A desire for adventure and discovery': 'Ranger',
        'The pursuit of knowledge and mastery': 'Wizard',
        'A commitment to a higher cause': 'Paladin',
        'The thrill of battle': 'Barbarian',
        'Hand-to-hand combat': 'Monk',
        'Playing musical instruments': 'Bard',
        'Crafting and using magic items': 'Wizard',
        'Tracking and survival': 'Ranger',
        'Bold and brash': 'Barbarian',
        'Intelligent and curious': 'Wizard',
        'Devout and righteous': 'Paladin',
        'Mysterious and cunning': 'Warlock',
        'A tale of epic battles and heroism': 'Fighter',
        'A mystical journey of magic and discovery': 'Sorcerer',
        'A sacred quest to vanquish evil': 'Paladin',
        'An adventure in the untamed wilds': 'Druid'
    }


# Initialize Pygame
pygame.init()
pygame.display.set_caption("D&D Class Quiz")
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
current_background = random.choice(background_images)
font = pygame.font.Font(None, 36)

# Game Variables
current_question_index = 0
answers = []
result = None

# Function to display text on the screen
def display_text(text, color, x, y):
    text_surface = font.render(text, True, color)
    text_rect = text_surface.get_rect()
    text_rect.center = (x, y)
    screen.blit(text_surface, text_rect)
    
# Function to display the current question
def display_question(question):
    # Draw a white rectangle around the question and choices
    question_box_width = 750
    question_box_height = 400
    question_box_x = (SCREEN_WIDTH - question_box_width) // 2
    question_box_y = (SCREEN_HEIGHT - question_box_height) // 2
    pygame.draw.rect(screen, WHITE, pygame.Rect(question_box_x, question_box_y, question_box_width, question_box_height))

    question_text_x = question_box_x + question_box_width // 2
    question_text_y = question_box_y + 50
    display_text(question["question"], BLACK, question_text_x, question_text_y)

    answer_y = question_text_y + 100
    for i, answer in enumerate(question["answers"]):
        display_text(f"{i + 1}. {answer}", BLACK, question_text_x, answer_y)
        answer_y += 50

# Function to display the result
def display_result(result):
    result_text = f"Your D&D Class is: {result}"
    result_surface = font.render(result_text, True, BLACK)
    result_rect = result_surface.get_rect()
    result_rect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(result_surface, result_rect)

# Game Loop
running = True
used_backgrounds = [] # Keep track of used backgrounds to avoid duplicates
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                answers.append(questions[current_question_index]["answers"][0])
                current_question_index += 1
                current_background = random.choice([bg for bg in background_images if bg not in used_backgrounds])
                if current_background:
                    used_backgrounds.append(current_background)
            elif event.key == pygame.K_2:
                answers.append(questions[current_question_index]["answers"][1])
                current_question_index += 1
                current_background = random.choice([bg for bg in background_images if bg not in used_backgrounds])
                if current_background:
                    used_backgrounds.append(current_background)
            elif event.key == pygame.K_3:
                answers.append(questions[current_question_index]["answers"][2])
                current_question_index += 1
                current_background = random.choice([bg for bg in background_images if bg not in used_backgrounds])
                if current_background:
                    used_backgrounds.append(current_background)
            elif event.key == pygame.K_4:
                answers.append(questions[current_question_index]["answers"][3])
                current_question_index += 1
                current_background = random.choice([bg for bg in background_images if bg not in used_backgrounds])
                if current_background:
                    used_backgrounds.append(current_background)

            # Check if all questions have been answered
            if current_question_index == len(questions):
                # Calculate the result
                class_scores = {}
                for answer in answers:
                    class_name = answer_mapping.get(answer)
                    if class_name:
                        class_scores[class_name] = class_scores.get(class_name, 0) + 1
                result = max(class_scores, key=class_scores.get)

    # Clear the screen
    screen.fill(BLACK)

    # Display the background image
    screen.blit(current_background, (0, 0))

    # Display the question or result
    if current_question_index < len(questions):
        display_question(questions[current_question_index])
    else:
        display_result(result)

    # Update the display
    pygame.display.flip()

# Quit Pygame
pygame.quit()
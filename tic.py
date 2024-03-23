import pygame
import sys

# Define constants
WIDTH, HEIGHT = 300, 300
LINE_WIDTH = 10
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
FPS = 60

# Initialize Pygame
pygame.init()
pygame.display.set_caption("Tic Tac Toe")
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# Initialize game variables
board = [['-' for _ in range(3)] for _ in range(3)]
current_player = 'O'
game_over = False
winner = None


def draw_grid():
    # Draw vertical lines
    for i in range(1, 3):
        pygame.draw.line(screen, WHITE, (i * WIDTH // 3, 0), (i * WIDTH // 3, HEIGHT), LINE_WIDTH)
    # Draw horizontal lines
    for i in range(1, 3):
        pygame.draw.line(screen, WHITE, (0, i * HEIGHT // 3), (WIDTH, i * HEIGHT // 3), LINE_WIDTH)


def draw_board():
    for row in range(3):
        for col in range(3):
            if board[row][col] == 'X':
                pygame.draw.line(screen, RED, (col * WIDTH // 3, row * HEIGHT // 3),((col + 1) * WIDTH // 3, (row + 1) * HEIGHT // 3), LINE_WIDTH)
                pygame.draw.line(screen, RED, ((col + 1) * WIDTH // 3, row * HEIGHT // 3),(col * WIDTH // 3, (row + 1) * HEIGHT // 3), LINE_WIDTH)
            elif board[row][col] == 'O':
                pygame.draw.circle(screen, BLUE, ((col + 0.5) * WIDTH // 3, (row + 0.5) * HEIGHT // 3),min(WIDTH, HEIGHT) // 6 - LINE_WIDTH // 2, LINE_WIDTH)


def check_win():
    global winner
    # Check rows and columns
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != '-':
            winner = board[i][0]
            return True
        if board[0][i] == board[1][i] == board[2][i] != '-':
            winner = board[0][i]
            return True
    # Check diagonals
    if board[0][0] == board[1][1] == board[2][2] != '-':
        winner = board[0][0]
        return True
    if board[0][2] == board[1][1] == board[2][0] != '-':
        winner = board[0][2]
        return True
    return False


def is_board_full():
    for row in board:
        for cell in row:
            if cell == '-':
                return False
    return True


def draw_text(text, font, color, surface, x, y):
    text_obj = font.render(text, True, color)
    text_rect = text_obj.get_rect()
    text_rect.center = (x, y)
    surface.blit(text_obj, text_rect)


def main():
    global current_player, game_over

    while not game_over:
        screen.fill(BLACK)

        draw_grid()
        draw_board()

        # Check for events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                mouseX, mouseY = pygame.mouse.get_pos()
                row = mouseY // (HEIGHT // 3)
                col = mouseX // (WIDTH // 3)

                if board[row][col] == '-':
                    board[row][col] = current_player
                    draw_board()
                    pygame.display.flip()
                    if check_win():
                        game_over = True
                    elif is_board_full():
                        game_over = True
                    else:
                        current_player = 'X' if current_player == 'O' else 'O'

        if game_over:
            if winner:
                draw_text(f"Player {1 if winner == 'O' else 2} wins!", pygame.font.Font(None, 32), (0,255,0), screen,
                          WIDTH // 2, HEIGHT // 2)
            else:
                draw_text("It's a draw!", pygame.font.Font(None, 32), (0,255,0), screen, WIDTH // 2, HEIGHT // 2)

            pygame.display.flip()
            pygame.time.wait(5000)

        pygame.display.flip()
        clock.tick(FPS)

if __name__ == "__main__":
    main()
    pygame.quit()
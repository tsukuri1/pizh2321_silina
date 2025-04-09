import pygame
import random
import json
import os

# Инициализация pygame
pygame.init()

# Константы игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
GRID_SIZE = 20
GRID_COLOR = (200, 200, 200)  # Светло-серый цвет сетки
OBSTACLE_COUNT = 10  # Количество препятствий

# Цвета
SALAD = (144, 238, 144)  # Салатовый фон
GREEN = (34, 139, 34)    # Темно-зеленый цвет змейки
RED = (255, 0, 0)        # Красный цвет еды
BLACK = (0, 0, 0)        # Чёрный текст
WHITE = (255, 255, 255)  # Белая обводка текста
OBSTACLE_COLOR = (70, 70, 70)  # Серый цвет препятствий

# Шрифты
font = pygame.font.SysFont('arial', 25, bold=True)  # Жирный шрифт для лучшей читаемости
big_font = pygame.font.SysFont('arial', 50, bold=True)

class Snake:
    def __init__(self):
        self.reset()
    
    def reset(self):
        self.positions = [(SCREEN_WIDTH//2, SCREEN_HEIGHT//2)]
        self.direction = 'RIGHT'
        self.length = 1
        self.score = 0
        self.speed = 10
        self.thickness = GRID_SIZE
        self.alive = True
        self.obstacles = self.generate_obstacles()
    
    def generate_obstacles(self):
        """Генерирует одноклеточные препятствия"""
        obstacles = []
        for _ in range(OBSTACLE_COUNT):
            while True:
                x = random.randrange(0, SCREEN_WIDTH, GRID_SIZE)
                y = random.randrange(0, SCREEN_HEIGHT, GRID_SIZE)
                # Проверяем, чтобы препятствие не было на стартовой позиции
                if (x != SCREEN_WIDTH//2 and y != SCREEN_HEIGHT//2):
                    break
            obstacles.append(pygame.Rect(x, y, GRID_SIZE, GRID_SIZE))
        return obstacles
    
    def move(self):
        if not self.alive:
            return
            
        head_x, head_y = self.positions[0]
        if self.direction == 'UP':
            new_head = (head_x, (head_y - GRID_SIZE) % SCREEN_HEIGHT)
        elif self.direction == 'DOWN':
            new_head = (head_x, (head_y + GRID_SIZE) % SCREEN_HEIGHT)
        elif self.direction == 'LEFT':
            new_head = ((head_x - GRID_SIZE) % SCREEN_WIDTH, head_y)
        elif self.direction == 'RIGHT':
            new_head = ((head_x + GRID_SIZE) % SCREEN_WIDTH, head_y)
            
        self.positions.insert(0, new_head)
        if len(self.positions) > self.length:
            self.positions.pop()
    
    def grow(self):
        self.length += 1
        self.score += 10
    
    def check_collision(self):
        head = self.positions[0]
        head_rect = pygame.Rect(head[0], head[1], self.thickness, self.thickness)
        
        # Столкновение с собой
        if head in self.positions[1:]:
            self.alive = False
        
        # Столкновение с препятствиями
        for obstacle in self.obstacles:
            if head_rect.colliderect(obstacle):
                self.alive = False
        
        return not self.alive

def draw_grid(surface):
    """Рисует сетку на игровом поле"""
    for x in range(0, SCREEN_WIDTH, GRID_SIZE):
        pygame.draw.line(surface, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
    for y in range(0, SCREEN_HEIGHT, GRID_SIZE):
        pygame.draw.line(surface, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

def render_outlined_text(text, font, text_color, outline_color):
    """Рендерит текст с обводкой для лучшей читаемости"""
    text_surface = font.render(text, True, text_color)
    outline_surface = font.render(text, True, outline_color)
    
    surface = pygame.Surface((text_surface.get_width() + 2, text_surface.get_height() + 2), pygame.SRCALPHA)
    
    # Рисуем обводку (смещаем на 1 пиксель в разные стороны)
    surface.blit(outline_surface, (0, 1))
    surface.blit(outline_surface, (2, 1))
    surface.blit(outline_surface, (1, 0))
    surface.blit(outline_surface, (1, 2))
    
    # Рисуем основной текст поверх обводки
    surface.blit(text_surface, (1, 1))
    
    return surface

def load_high_score():
    """Загружает рекорд из файла"""
    if os.path.exists('highscore.json'):
        try:
            with open('highscore.json', 'r') as f:
                return json.load(f).get('highscore', 0)
        except:
            return 0
    return 0

def save_high_score(score):
    """Сохраняет рекорд в файл"""
    with open('highscore.json', 'w') as f:
        json.dump({'highscore': score}, f)

def main():
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption('Змейка с препятствиями')
    clock = pygame.time.Clock()
    
    snake = Snake()
    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
            random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
    high_score = load_high_score()
    running = True
    
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if not snake.alive and event.key == pygame.K_SPACE:
                    snake.reset()
                    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                           random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
                elif snake.alive:
                    if event.key == pygame.K_UP and snake.direction != 'DOWN':
                        snake.direction = 'UP'
                    elif event.key == pygame.K_DOWN and snake.direction != 'UP':
                        snake.direction = 'DOWN'
                    elif event.key == pygame.K_LEFT and snake.direction != 'RIGHT':
                        snake.direction = 'LEFT'
                    elif event.key == pygame.K_RIGHT and snake.direction != 'LEFT':
                        snake.direction = 'RIGHT'
        
        if snake.alive:
            snake.move()
            
            # Проверка съедания еды
            if snake.positions[0] == food:
                snake.grow()
                food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                       random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
                # Убеждаемся, что еда не появилась в змейке или на препятствиях
                while (food in snake.positions or 
                       any(food[0] == obs.x and food[1] == obs.y for obs in snake.obstacles)):
                    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                           random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
            
            # Проверка столкновений
            if snake.check_collision():
                if snake.score > high_score:
                    high_score = snake.score
                    save_high_score(high_score)
        
        # Отрисовка игры
        screen.fill(SALAD)  # Заливаем салатовым фоном
        draw_grid(screen)   # Рисуем сетку
        
        # Рисуем препятствия
        for obstacle in snake.obstacles:
            pygame.draw.rect(screen, OBSTACLE_COLOR, obstacle)
        
        # Рисуем змейку
        for pos in snake.positions:
            pygame.draw.rect(screen, GREEN, (pos[0], pos[1], snake.thickness, snake.thickness))
        
        # Рисуем еду
        pygame.draw.rect(screen, RED, (food[0], food[1], snake.thickness, snake.thickness))
        
        # Отображаем счёт с обводкой (чёрный текст с белой обводкой)
        score_text = render_outlined_text(f'Счет: {snake.score}', font, BLACK, WHITE)
        high_score_text = render_outlined_text(f'Рекорд: {high_score}', font, BLACK, WHITE)
        screen.blit(score_text, (10, 10))
        screen.blit(high_score_text, (10, 40))
        
        # Сообщение Game Over
        if not snake.alive:
            game_over_text = big_font.render('Конец игры!', True, RED)
            restart_text = font.render('Нажми ПРОБЕЛ', True, WHITE)
            screen.blit(game_over_text, (SCREEN_WIDTH//2 - game_over_text.get_width()//2, SCREEN_HEIGHT//2 - 50))
            screen.blit(restart_text, (SCREEN_WIDTH//2 - restart_text.get_width()//2, SCREEN_HEIGHT//2 + 20))
        
        pygame.display.flip()  # Обновляем экран
        clock.tick(snake.speed if snake.alive else 60)  # Контроль FPS
    
    pygame.quit()  # Выход из игры

if __name__ == "__main__":
    main()
import pygame
import random
import os
import json
from pygame import mixer

# Настройки игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
GRID_SIZE = 20
INITIAL_SPEED = 10
SPEED_INCREMENT = 0.5
SNAKE_GROWTH = 3

class Snake:
    def __init__(self):
        self.reset()
        self.body_colors = [
            (100, 200, 100),  # Светло-зеленый
            (80, 180, 80),    # Средне-зеленый
            (60, 160, 60)     # Темно-зеленый
        ]
        
    def reset(self):
        self.positions = [(SCREEN_WIDTH//2, SCREEN_HEIGHT//2)]
        self.direction = 'RIGHT'
        self.length = 5
        self.score = 0
        self.speed = INITIAL_SPEED
        self.thickness = GRID_SIZE
        self.alive = True
        self.obstacles = self.generate_obstacles()
    
    def generate_obstacles(self):
        # Создаем 5 случайных препятствий
        obstacles = []
        for _ in range(5):
            x = random.randrange(0, SCREEN_WIDTH - 100, GRID_SIZE)
            y = random.randrange(0, SCREEN_HEIGHT - 100, GRID_SIZE)
            width = random.randrange(2, 5) * GRID_SIZE
            height = random.randrange(2, 5) * GRID_SIZE
            obstacles.append(pygame.Rect(x, y, width, height))
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
        self.length += SNAKE_GROWTH
        self.score += 10
        self.speed += SPEED_INCREMENT

    def check_collision(self):
        head = self.positions[0]
        # Проверка столкновения с собой
        if head in self.positions[1:]:
            self.alive = False
        # Проверка столкновения с препятствиями
        head_rect = pygame.Rect(head[0], head[1], self.thickness, self.thickness)
        for obstacle in self.obstacles:
            if head_rect.colliderect(obstacle):
                self.alive = False
        return not self.alive
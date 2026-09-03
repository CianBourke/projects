import pygame

pygame.init()

screen = pygame.display.set_mode((1100,800))
clock = pygame.time.Clock()

#while the game is running
game_running = True


# class player is the player its inheriting features/actions from sprite class
class Player(pygame.sprite.Sprite):
    
    # def init allows entered sprite to intialize
    #self is assigned to p1 and type is 1st feature entered
    def __init__(self,pos):
        super().__init__()
        #creates an image in the form of rectangle
        self.image = pygame.Surface((20,20))
        #creates a reactangle and assign position
        self.rect = self.image.get_rect(center = pos)
        
        # movement
        # first x -1 second 1 y its where the self intends to go
        self.intent = [0,0]
        #function called movement uses self for movement
    def movement(self):
        # allows self.rect to increase by intent
        self.rect.x += self.intent[0]* 8
        self.rect.y += self.intent[1]* 8
        
    
        
    
p1 = Player((200,500))


while game_running:
    #screen.fill colours in screen numbers are rgb
    screen.fill((200,250,200))
    
    # for each event in game pygame.event.get() used for sifting through list
    for event in pygame.event.get():
        #to quit need to add code to quit adds x to quit if event is same as pygame quit
        if event.type == pygame.QUIT:
            quit()
        # if event type is keydown(pressed down) then check keys and display actions
        elif event.type == pygame.KEYDOWN:
            # searching through to find type == kup kup = key
            if event.key == pygame.K_UP:
                p1.intent[1] = -1
            elif event.key == pygame.K_DOWN:
                p1.intent[1] = 1
            elif event.key == pygame.K_LEFT:
                p1.intent[0] = -1
        
            elif event.key == pygame.K_RIGHT:
                p1.intent[0]= 1
                
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_UP:
                p1.intent[1] = 0
            elif event.key == pygame.K_DOWN:
                p1.intent[1] = 0
            elif event.key == pygame.K_LEFT:
                p1.intent[0] = 0
        
            elif event.key == pygame.K_RIGHT:
                p1.intent[0]= 0
        
                

        
    p1.movement()
    
    #this will draw and display the image p1= image rect = rectangle
    screen.blit(p1.image,p1.rect)
    
    
    
    #to display what you have coded you need to end with
    pygame.display.update()
    #to have the game know how long to wait before starting the next loop the fps
    clock.tick(60)
   
    

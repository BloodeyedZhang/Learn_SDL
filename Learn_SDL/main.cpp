//
//  main.cpp
//  Learn_SDL
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, const char * argv[]) {
    bool quit = false;
    SDL_Event event;
    // 声明表面
    SDL_Surface* hello = NULL;
    SDL_Window* screen = NULL;
    // 启动SDL
    SDL_Init(SDL_INIT_VIDEO);
    // 额外使用了图片库,需要单独初始化
    IMG_Init(IMG_INIT_JPG);
    // 设置窗口
    screen = SDL_CreateWindow(
                                        "hello",    // 标题
                                        100,             // 窗体左上角的x坐标
                                        100,             // 窗体左上角的y坐标
                                        1024,            // 窗体宽度
                                        768,             // 窗体高度
                                        0                //标志位
                                        );
    // 加载渲染器
    SDL_Renderer* mRenderer = SDL_CreateRenderer(
                                   screen,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                   );
    // 加载图像
    hello = IMG_Load("/Users/zhangjiajun/work/MyLearning/Learn_SDL/Resources/hello.png");
    // 加载纹理
    SDL_Texture* mTexture = SDL_CreateTextureFromSurface(mRenderer, hello);
    while (!quit) {
        SDL_WaitEvent(&event);
        
        switch (event.type) {
                // 用户从菜单要求退出程序
            case SDL_QUIT:
                quit = true;
                break;
                
            default:
                break;
        }
        // 把贴图材质复制到渲染器上
        SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
        // 显示出来
        SDL_RenderPresent(mRenderer);
    }
    
    SDL_DestroyTexture(mTexture);
    SDL_FreeSurface(hello);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(screen);
    
    IMG_Quit();
    
    SDL_Quit();
    return 0;
}

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
    // 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建窗口
    SDL_Window* mWindow = nullptr;
    mWindow = SDL_CreateWindow("hello world", 100, 100, 640, 640, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建渲染器
    SDL_Renderer* mRender = nullptr;
    mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRender == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    // 加载bmp格式图片
    SDL_Surface* mSurface = nullptr;
    mSurface = SDL_LoadBMP("/Users/zhangjiajun/work/MyLearning/Learn_SDL/Resources/hello.bmp");
    if (mSurface == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* mTexture = nullptr;
    mTexture = SDL_CreateTextureFromSurface(mRender, mSurface);
    SDL_FreeSurface(mSurface); //释放surface
    // 绘制图像
    SDL_RenderClear(mRender);  //清空渲染器
    SDL_RenderCopy(mRender, mTexture, NULL, NULL); //画图像
    SDL_RenderPresent(mRender); //更新屏幕
    // 延迟2000毫秒
    SDL_Delay(2000);
    // 释放内存
    SDL_DestroyTexture(mTexture);
    SDL_DestroyRenderer(mRender);
    SDL_DestroyWindow(mWindow);
    
    SDL_Quit();
    
    
    /*
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
     */
    return 0;
}

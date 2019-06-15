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
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* mWindow = nullptr;
SDL_Renderer* mRenderer = nullptr;

SDL_Texture* LoadImage(std::string filename, SDL_Renderer* mRenderer) {
    SDL_Texture* mTexture = nullptr;
    mTexture = IMG_LoadTexture(mRenderer, filename.c_str());
    if (mTexture == nullptr)
        throw std::runtime_error("Fail to load image: " + filename + SDL_GetError());
    return mTexture;
}

void ApplySurface(int x, int y, SDL_Texture* mTexture, SDL_Renderer* mRenderer) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(mTexture, NULL, NULL, &pos.w, &pos.h);
    
    SDL_RenderCopy(mRenderer, mTexture, NULL, &pos);
}

int main(int argc, const char * argv[]) {
    bool quit = false;
    SDL_Event event;
    // 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    // 额外使用了图片库,需要单独初始化
    IMG_Init(IMG_INIT_JPG);
    // 创建窗口
    mWindow = SDL_CreateWindow("lesson 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }
    // 创建渲染器
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }
    
    // 加载bmp格式图片
    SDL_Texture *mBackground = nullptr, *mSmile = nullptr;
    std::string resRoot = "/Users/zhangjiajun/work/MyLearning/Learn_SDL/Resources/lesson3/";
    try {
        mBackground = LoadImage((resRoot + "background.png").c_str(), mRenderer);
        mSmile = LoadImage((resRoot + "image.png").c_str(), mRenderer);
    }
    catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 4;
    }
    // 绘制图像
    SDL_RenderClear(mRenderer);  //清空渲染器
    int bw, bh, iw, ih, colCnt = 2, rowCnt = 2;
    SDL_QueryTexture(mBackground, NULL, NULL, &bw, &bh);
    SDL_QueryTexture(mSmile, NULL, NULL, &iw, &ih);
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
        // 绘制背景
        for (int i = 0; i < colCnt; i++) {
            for (int j = 0; j < rowCnt; j++) {
                ApplySurface(bw*i, bh*j, mBackground, mRenderer);
            }
        }
        // 绘制前景
        ApplySurface(SCREEN_WIDTH/2 - iw/2, SCREEN_HEIGHT/2 - ih/2, mSmile, mRenderer);
        
        // 显示出来
        SDL_RenderPresent(mRenderer);
    }
    
    
    // 释放内存
    SDL_DestroyTexture(mBackground);
    SDL_DestroyTexture(mSmile);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    
    
    IMG_Quit();
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

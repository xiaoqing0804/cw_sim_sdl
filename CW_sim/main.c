#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 初始化失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("Green Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        return 1;
    }

    // 获取窗口的渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        return 1;
    }

    // 设置背景颜色为绿色
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // R, G, B, Alpha
    SDL_RenderClear(renderer);

    // 更新窗口显示
    SDL_RenderPresent(renderer);

    // 等待用户关闭窗口
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // 清理资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
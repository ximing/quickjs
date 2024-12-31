#include "quickjs-libc.h"

int main(int argc, char **argv) {
  // 创建一个新的QuickJS运行时
  JSRuntime *rt = JS_NewRuntime();
  if (!rt) {
    fprintf(stderr, "Failed to create JS runtime\n");
    return 1;
  }

  // 创建一个新的上下文
  JSContext *ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "Failed to create JS context\n");
    JS_FreeRuntime(rt);
    return 1;
  }

  // 手动添加所需的内置对象和功能
  JS_AddIntrinsicBaseObjects(ctx); // 基础对象，如 Object, Function, Array
  JS_AddIntrinsicMapSet(ctx);      // 添加 Map 和 Set
  JS_AddIntrinsicRegExp(ctx);      // 添加正则表达式支持

  // 初始化标准库（如果需要使用标准I/O等功能）
  js_std_init_handlers(rt);
  js_std_add_helpers(ctx, argc, argv);

  // 执行字节码
  js_std_eval_binary(ctx, qjsc_test, qjsc_test_size, 0);

  // 进入事件循环
  js_std_loop(ctx);

  // 释放资源
  JS_FreeContext(ctx);
  JS_FreeRuntime(rt);

  return 0;
}

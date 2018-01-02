//
//  JPEngine.h
//  JSPatch
//
//  Created by bang on 15/4/30.
//  Copyright (c) 2015 bang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>
/*
 注:Objective-C (简称 OC),JavaScript(简称JS),下同
 */

@interface JPEngine : NSObject

/*!
 @method
 @discussion 启动JSPatch引擎，只执行一次
 !Deprecated! 将在评估脚本之前自动调用
 */
+ (void)startEngine;

/*!
 @method
 @description 从文件路径中评估Javascript代码. 在+startEngine后调用.
 @param filePath: Javascript代码的文件路径.
 @result 脚本生成的最后一个值.
 */
+ (JSValue *)evaluateScriptWithPath:(NSString *)filePath;

/*!
 @method
 @description 评估JavaScript代码字符串. 在+startEngine后调用.
                在Safari调试器中,该方法讲生成一个默认名为"main.js"的resouceURL
 @param script: 一个包含JavaScript代码的字符串
 @result 脚本生成的最后一个值。
 */
+ (JSValue *)evaluateScript:(NSString *)script;

/*!
 @method
 @description 返回JSPatch JavaScript执行环境(上下文).
 */
+ (JSContext *)context;



/*!
 @method
 @description 添加JPExtension.
 @param extensions: 包含类名 字符串的数组.
 */
+ (void)addExtensions:(NSArray *)extensions;

/*!
 @method
 @description 添加支持JS的新结构体类型
 @param defineDict: 结构体的定义, 例如:
    @{
      @"name": @"CGAffineTransform",   //struct name
      @"types": @"ffffff",  //struct types
      @"keys": @[@"a", @"b", @"c", @"d", @"tx", @"ty"]  //struct keys in JS
    }
 */
+ (void)defineStruct:(NSDictionary *)defineDict;

+ (void)handleException:(void (^)(NSString *msg))exceptionBlock;
@end



@interface JPExtension : NSObject
+ (void)main:(JSContext *)context;

+ (void *)formatPointerJSToOC:(JSValue *)val;
+ (id)formatRetainedCFTypeOCToJS:(CFTypeRef)CF_CONSUMED type;
+ (id)formatPointerOCToJS:(void *)pointer;
+ (id)formatJSToOC:(JSValue *)val;
+ (id)formatOCToJS:(id)obj;

+ (int)sizeOfStructTypes:(NSString *)structTypes;
+ (void)getStructDataWidthDict:(void *)structData dict:(NSDictionary *)dict structDefine:(NSDictionary *)structDefine;
+ (NSDictionary *)getDictOfStruct:(void *)structData structDefine:(NSDictionary *)structDefine;

/*!
 @method
 @description 返回在JSPatch中已定义的结构体.
 the key of dictionary is the struct name.
 */
+ (NSMutableDictionary *)registeredStruct;

+ (NSDictionary *)overideMethods;
+ (NSMutableSet *)includedScriptPaths;
@end



@interface JPBoxing : NSObject
@property (nonatomic) id obj;
@property (nonatomic) void *pointer;
@property (nonatomic) Class cls;
@property (nonatomic, weak) id weakObj;
@property (nonatomic, assign) id assignObj;
- (id)unbox;//拆箱
- (void *)unboxPointer;//拆箱-指针
- (Class)unboxClass;//拆箱-类
@end


//
//  NSSet+BlocksKit.h
//  %PROJECT
//

#import "BKGlobals.h"

/** Block extensions for NSSet.

 Both inspired by and resembling Smalltalk syntax, these utilities
 allows for iteration of a set in a logical way that
 saves quite a bit of boilerplate code for filtering or finding
 objects or an object.

 Includes code by the following:

- Michael Ash.	<https://github.com/mikeash>.	2010. BSD.
- Corey Floyd.	<https://github.com/coreyfloyd>. 2010.
- Aleks Nesterow. <https://github.com/nesterow>.   2010. BSD.
- Zach Waldowski. <https://github.com/zwaldowski>. 2011. MIT.

 @see NSArray(BlocksKit)
 @see NSDictionary(BlocksKit)
 */
@interface NSSet (BlocksKit)

/** Loops through a set and executes the given block with each object.

 @param block A single-argument, void-returning code block.
 */
- (void)each:(BKSenderBlock)block;

/** Enumerates through a set concurrently and executes
 the given block once for each object.
 
 Enumeration will occur on appropriate background queues. This
 will have a noticeable speed increase, especially on dual-core
 devices, but you *must* be aware of the thread safety of the
 objects you message from within the block.
 
 @param block A single-argument, void-returning code block.
 */
- (void)apply:(BKSenderBlock)block;

/** Loops through a set to find the object matching the block.

 match: is functionally identical to select:, but will stop and return
 on the first match.

 @param block A single-argument, BOOL-returning code block.
 @return Returns the object if found, `nil` otherwise.
 @see select:
 */
- (id)match:(BKValidationBlock)block;

/** Loops through a set to find the objects matching the block.

 @param block A single-argument, BOOL-returning code block.
 @return Returns a set of the objects found, `nil` otherwise.
 @see match:
 */
- (NSSet *)select:(BKValidationBlock)block;

/** Loops through a set to find the objects not matching the block.

 This selector performs *literally* the exact same function as select, but in reverse.

 This is useful, as one may expect, for removing objects from a set:
	 NSSet *new = [reusableWebViews reject:^BOOL(id obj) {
	   return ([obj isLoading]);
	 }];

 @param block A single-argument, BOOL-returning code block.
 @return Returns an array of all objects not found, `nil` if all are excluded.
 */
- (NSSet *)reject:(BKValidationBlock)block;

/** Call the block once for each object and create a set of the return values.
 
 This is sometimes referred to as a transform, mutating one of each object:
	 NSSet *new = [mimeTypes map:^id(id obj) {
	   return [@"x-company-" stringByAppendingString:obj]);
	 }];

 @param block A single-argument, object-returning code block.
 @return Returns a set of the objects returned by the block.
 */
- (NSSet *)map:(BKTransformBlock)block;

/** Arbitrarily accumulate objects using a block.

 The concept of this selector is difficult to illustrate in words. The sum can
 be any NSObject, including (but not limited to) an NSString, NSNumber, or NSValue.

 You can also do something like summing the count of an item:
	 NSNumber *sum = [bodyList reduce:nil withBlock:^id(id sum, id obj) {
	   return [NSNumber numberWithInteger: [sum integerValue] + obj.numberOfAppendages];
	 }];
	 NSUInteger numberOfBodyParts = [sum integerValue];

 @param initial The value of the reduction at its start.
 @param block A block that takes the current sum and the next object to return the new sum.
 @return An accumulated value.
 */
- (id)reduce:(id)initial withBlock:(BKAccumulationBlock)block;

@end
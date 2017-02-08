/**
 * @file   buffer_b64encode.c
 * @author Reginald Lips <reginald.l@gmail.com> - Copyright 2017
 * @date   Tue Feb  7 20:41:55 2017
 *
 * @brief  rn_buffer_b64encode unit test
 *
 *
 */

#include "rinoo/rinoo.h"

void check_buf(rn_buffer_t *buffer, const char *expected_result)
{
	rn_buffer_t *dst;

	dst = rn_buffer_create(NULL);
	XTEST(rn_buffer_b64encode(dst, buffer) == 0);
	XTEST(rn_buffer_strcmp(dst, expected_result) == 0);
	rn_buffer_destroy(dst);
}

/**
 * Main function for this unit test
 *
 *
 * @return 0 if test passed
 */
int main()
{
	rn_buffer_t buffer;

	rn_buffer_set(&buffer, "this is a test.");
	check_buf(&buffer, "dGhpcyBpcyBhIHRlc3Qu");
	rn_buffer_static(&buffer,
			"\000\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\021\022\023\024\025\026\027\030"
			"\031\032\033\034\035\036\037\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057\060\061"
			"\062\063\064\065\066\067\070\071\072\073\074\075\076\077\100\101\102\103\104\105\106\107\110\111\112"
			"\113\114\115\116\117\120\121\122\123\124\125\126\127\130\131\132\133\134\135\136\137\140\141\142\143"
			"\144\145\146\147\150\151\152\153\154\155\156\157\160\161\162\163\164\165\166\167\170\171\172\173\174"
			"\175\176\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225"
			"\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256"
			"\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307"
			"\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340"
			"\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371"
			"\372\373\374\375\376\377",
			256);
	check_buf(&buffer,
			"AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4"
			"OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3Bx"
			"cnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmq"
			"q6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj"
			"5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==");
	XPASS();
}

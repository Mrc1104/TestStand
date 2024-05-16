#ifndef TEST_TRIGGER_TABLE_H
#define TEST_TRIGGER_TABLE_H

//unsigned int tiTable_coinc_test[16] = { 
//	/* TS# 1, 4, 6      generate Trigger 1 (Physics) */
//	/* TS# 1 & 6, 1 & 4 generate Trigger 2 (Physics) */
//	0x03024100, 0x07060504, 0x0b0a8948, 0x0f0e0d0c,
//	0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
//	0x23226160, 0x27262524, 0x2b2a2928, 0x2f2e2d2c,
//	0x33323130, 0x37363534, 0x3b3a3938, 0x3f3e3d3c,
//};

unsigned int tiTable_coinc_test[16] = { 
	/* TS# 1,2,3,4,5,6      generate Trigger 1 (Physics) */
	/* TS# 1&6, 1&2, 1&3, 1&4, 1&5 generate Trigger 2 (Physics) */
	0x83424100, 0x07068544, 0x0b0a8948, 0x0f0e0d0c,
	0x13129150, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
	0x2322a160, 0x27262524, 0x2b2a2928, 0x2f2e2d2c,
	0x33323130, 0x37363534, 0x3b3a3938, 0x3f3e3d3c,
};

#endif

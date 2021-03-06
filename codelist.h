#error codelist is not a real header


// ==========================================================================
// Data Manipulation

typedef uint8 size{0,32,1};
typedef uint{8,256,8} constant;

typedef struct {
	bool sign;
	uint7 size;
} signsize;

typedef struct {
	bool direction;
	uint7 size;
} dirsize;

typedef struct {
	signsize;
	int16 place;
} signsizeplace;


// Memory
0x0001	CPY	size X,		address in,	address out
0x0002	MOV	size X,		address in,	address out
0x0003	SWAP	size X,		address A,	address B

// Basic Arithmetic
0x0010	ADD	signsize A,	address A,	signsize B,	address B
		signsize out,	address out
0x0012	MUL	signsize A,	address A,	signsize B,	address B
		signsize out,	address out
0x0013	INV	signsize X,	address in,	address out

// Bit Shifts
0x0020	SHF	dirsize X,	address in,	address out
0x0021	ROT	dirsize X,	address in,	address out

// Bitwise Arithmetic
0x0030	BOR	size X,		address A,	address B,	address out
0x0031	BAND	size X,		address A,	address B,	address out
0x0032	BXOR	size X,		address A,	address B,	address out

// oc Floating Point Arithmetic
0x0040	ADDF	signsizeplace A,		address A,
		signsizeplace B,		address B,
		signsizeplace out,		address out
0x0042	MULF	signsizeplace A,		address A,
		signsizeplace B,		address B,
		signsizeplace out,		address out
0x0043	INVF	signsizeplace X,		address in,	address out

// Increment / Decrement
0x0050	INC	signsize X,	address X
0x0051	DEC	signsize X,	address X

// oc Floating Point Increment / Decrement
0x0080	INCF	signsizeplace X,		address X
0x0081	DECF	signsizeplace X,		address X

// Value Manipulation
0x0060	SSP	signsizeplace in,		address in,
		signsizeplace out,		address out
0x0061	SET	size out,	constant out,	address out

// Logic
0x0070	EQL	signsizeplace in,		address in,	address out
0x0071	ORL	address A,	address B,	address out
0x0072	ANDL	address A,	address B,	address out
0x0073	XORL	address A,	address B,	address out

// Comparison
0x0090	ISL	signsize X,	address A,	address B,	address out
0x0091	UNDL	signsize X,	address A,	address B,	address out
0x0092	ABOL	signsize X,	address A,	address B,	address out

// Combinational Logic
0x0100	HAL	address A,	address B,	address S,	address C
0x0101	FAL	address A,	address B,	address S,	address Cin
		address Cout


// ==========================================================================
// Overall Program & Control Flow

typedef int32 relative;


// Start / End
0xF001	ENTR	stack:head
0xF002	EXIT	stack:ret

// Functions
0xF010	CALL	address func,	stack:args
0xF011	RET	stack:data

// Stack
0xF020	PUSH	size in,	address in
0xF021	POP	size out,	address out
0xF022	PUT	size in,	address rel,	address in
0xF023	PEEK	size out,	address rel,	address out

// Control / Flow
0xF030	COND	address true
0xF031	JUMP	relative position
0xF032	SKIP	int16 cycles

// Special Control Flow
0xF040	FORS	address X,	address Y,	address Z
0xF041	FORD	NULL16


// ==========================================================================
// Hardware Interfacing

typedef int16 line;

// Setup
0x4001	DETL	line check,	address out
0x4002	ENBL	line enable,	address out
0x4003	DSBL	line disable,	address out
0x4004	INITL	line start,	address out
0x4005	DNITL	line end,	address out

// R / W
0x4010	RXL	size X,		line in,	address out
0x4011	TXL	size X,		line out,	address in

var runtime = {
	stackPtr:0,
	stack:[],

	pushInt:function(i) {
		this.stack[this.stackPtr++] = i;
	}
};

function test() {

}

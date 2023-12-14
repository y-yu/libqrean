#include <stdio.h>

#include "hexdump.h"
#include "qrdata.h"
#include "qrmatrix.h"
#include "qrstream.h"

#include "barcode.h"

// return 1 to skip drawing
bit_t write_pixel(qrmatrix_t *qr, bitpos_t x, bitpos_t y, bitpos_t idx, bit_t v) {
	/*
	    char buffer[8192];
	    size_t len = qrmatrix_read_bitmap(qr, buffer, sizeof(buffer), 8);

	    printf("P5\n%d %d\n255\n", qr->symbol_size, qr->symbol_size);
	    fwrite(buffer, 1, len, stdout);
	*/
	return 0;
}

bit_t read_pixel(qrmatrix_t *qr, bitpos_t x, bitpos_t y, bitpos_t idx) {
	return 1;
}

int main() {
	qrmatrix_t qr = create_qrmatrix();
	qrmatrix_set_version(&qr, 3);
	qrmatrix_set_errorlevel(&qr, 1);
	qrmatrix_set_maskpattern(&qr, 1);

	// qrmatrix_on_write_pixel(&qr, write_pixel);
	//	qrmatrix_on_read_pixel(&qr, read_pixel);

	//qrmatrix_write_string(&qr, "Hello, world, 1234567");
	qrmatrix_write_string(&qr, "1234567, Hello, world, 1234567");

	char buffer[1024];
	qrmatrix_read_string(&qr, buffer, sizeof(buffer));
	printf("recv; %s\n", buffer);

	qrmatrix_dump(&qr, 1);

	barcode_t code = create_barcode(BARCODE_TYPE_EAN13);
	if (barcode_write_string(&code, "123456789012")) {
		barcode_dump(&code, 10);
	}

#if 0
	qrmatrix_write_pixel(&qr, qr.symbol_size - 1, qr.symbol_size - 1, 0);

	qrmatrix_dump(&qr, 1);

	qrmatrix_fix_errors(&qr);
	qrmatrix_dump(&qr, 1);
#endif
}
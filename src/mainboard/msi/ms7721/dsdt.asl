/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 * Copyright (C) 2013 Sage Electronic Engineering, LLC
 * Copyright (C) 2016 Renze Nicolai <renze@rnplus.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* DefinitionBlock Statement */
#include <arch/acpi.h>
DefinitionBlock (
	"DSDT.AML",		/* Output filename */
	"DSDT",			/* Signature */
	0x02,			/* DSDT Revision, needs to be 2 for 64bit */
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x00010001		/* OEM Revision */
	)
{	/* Start of ASL file */
	#include <arch/x86/acpi/debug.asl>	/* Include global debug methods if needed */

	/* Globals for the platform */
	#include "acpi/mainboard.asl"

	/* PCI IRQ mapping for the Southbridge */
	#include <southbridge/amd/agesa/hudson/acpi/pcie.asl>

	/* Describe the processor tree (\_PR) */
	#include <cpu/amd/agesa/family15tn/acpi/cpu.asl>

	/* Describe the supported Sleep States for this Southbridge */
	#include <southbridge/amd/common/acpi/sleepstates.asl>

	/* Describe the Sleep Methods (WAK, PTS, GTS, etc.) for this platform */
	#include "acpi/sleep.asl"

	Scope(\_SB) {
		/* global utility methods expected within the \_SB scope */
		#include <arch/x86/acpi/globutil.asl>

		/* Describe IRQ Routing mapping for this platform (within the \_SB scope) */
		#include "acpi/routing.asl"

		Device(PWRB) {
			Name(_HID, EISAID("PNP0C0C"))
			Name(_UID, 0xAA)
			Name(_PRW, Package () {3, 0x04})
			Name(_STA, 0x0B)
		}

		Device(PCI0) {
			/* Describe the AMD Northbridge */
			#include <northbridge/amd/agesa/family15tn/acpi/northbridge.asl>

			/* Describe the AMD Fusion Controller Hub Southbridge */
			#include <southbridge/amd/agesa/hudson/acpi/fch.asl>
		}

		/* Describe PCI INT[A-H] for the Southbridge */
		#include <southbridge/amd/agesa/hudson/acpi/pci_int.asl>

		/* Describe USB for the Southbridge */
		#include <southbridge/amd/agesa/hudson/acpi/usb.asl>

	}   /* End Scope(_SB)  */

	/* Describe SMBUS for the Southbridge */
	#include <southbridge/amd/agesa/hudson/acpi/smbus.asl>

	/* Define the General Purpose Events for the platform */
	#include "acpi/gpe.asl"

	/* Define the Thermal zones and methods for the platform */
	#include "acpi/thermal.asl"

	/* Define the System Indicators for the platform */
	#include "acpi/si.asl"

}
/* End of ASL file */

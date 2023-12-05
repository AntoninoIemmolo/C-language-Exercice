#include <stdio.h>
#include <stdlib.h>
#include "pg.h"

int main(){
	FILE* FPg=fopen("../input files-6/E3/pg.txt","r");
	FILE* FInv=fopen("../input files-6/E3/inventario.txt","r");
	if(NULL==FPg||NULL==FInv)
		return -1;
	PG_FileRead(FPg);
	EQ_FileRead(FInv);
	PG_InvIns("PG0003","Excalibur");
	PG_InvIns("PG0003","Filatterio");
	PG_InvIns("PG0003","Pendragon");
	PG_InvIns("PG0003","AmmazzaDraghi");
	PG_InvIns("PG0003","CorazzaAdamantina");
	PG_InvIns("PG0003","Oricalco");
	PG_InvIns("PG0003","Tempesta");
	PG_InvIns("PG0003","Maximillian");
	PG_InvIns("PG0003","DagaRunica");
	PG_InvIns("PG0003","ArmillaDiDiamante");
	PG_Print("PG0003");

	return 0;
}


#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>

/*
GenBank 	                                    gi|numéro gi|gb|numéro d'accession|locus
EMBL                                        	gi|numéro gi|emb|numéro d'accession|locus
DNA Data Bank of Japan 	                        gi|numéro gi|dbj|numéro d'accession|locus

GenBank 	                                    gb|accession|locus

EMBL 	                                        emb|accession|locus

NBRF PIR 	                                    pir||entrée
PIR 	                                        pir|accession|name 
Protein Research Foundation 	                prf|accession|name

Swiss-Prot 	                                    sp|numéro d'accession|nom

Brookhaven Protein Data Bank (1) 	            pdb|entrée|chaîne

Brookhaven Protein Data Bank (2) 	            entrée:chaîne|PDBID|CHAÎNE|SÉQUENCE

Brevets 	                                    pat|brevet|numéro
patent 	                                        pat|country|patent|sequence-number
pre-grant patent 	                            pgp|country|application-number|sequence-number 

GenInfo Backbone Id 	                        bbs|numéro
GenInfo backbone moltype 	                    bbm|integer

GenInfo import ID 	                            gim|integer
GenInfo integrated database 	                gi|integer
General database identifier 	                gnl|base de données|identifiant

NCBI Reference Sequence 	                    ref|numéro d'accession|locus / name
Local Sequence identifier 	                    lcl|identifiant
DDBJ 	dbj|accession|locus

third-party GenBank 	                        tpg|accession|name
third-party EMBL 	                            tpe|accession|name
third-party DDBJ 	                            tpd|accession|name 

TrEMBL 	                                        tr|accession|name


(ID, Number of |)
*/

class Header
{
private:
    // Inf
    // Des
    // Mod
    std::string comment;

    /*
    std::string format;
    std::map<std::string, std::string> specifiers;
    std::map<std::string, std::string> main;
    
    static std::map<std::string, std::string> known_format;
    */

public:
    std::string getComment () {return this->comment;};
    void setComment (std::string comment) { this->comment = comment;};
    
    // void static clear_string(std::string&) {};

};

#endif
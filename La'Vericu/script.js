const DB = {
  settings: {
    anEpicentru: 2010,
    factorAn: 0.08, // Creștere 8% per an distanță
    tva: 0.19,
    tarifOrarBaza: 150, // Lei pe ora
  },
  // Prețuri brute pentru fiecare obiect în parte
  piese_globale: {
    // ... cele vechi rămân ...
    ulei_bidon: 120,
    saiba_cupru: 5,
    sarma_otel: 2,
    filtru_ulei: 45,
    turbina_avion: 4500,
    prezon_otel: 15,
    garnitura_foc: 120,
    ulei_racing: 450,
    // PIESE NOI
    soft_st1: 800,
    soft_st2: 1500,
    soft_st3: 3000,
    admisie_aer: 600,
    filtru_sport: 250,
    intercooler_mare: 1200,
    turbo_hibrid: 2800,
    twin_turbo: 7500,
    supercharger: 9000,
    bov_valva: 400,
    downpipe: 900,
    evacuare_full: 2500,
    catalizator_sport: 1100,
    teava_decat: 300,
    pompa_benzina: 850,
    injectoare_mari: 1800,
    volanta_masa_simpla: 1400,
    ambreiaj_perfor: 2200,
    short_shifter: 350,
    launch_control: 500,
    coilover_set: 3200,
    arcuri_sport: 700,
    perne_aer: 8500,
    strut_bar: 300,
    bucse_poliuretan: 550,
    brake_pads: 450,
    big_brake_kit: 5500,
    jante_aliaj: 4000,
    cauciucuri_slick: 2400,
    spacers: 400,
    widebody_kit: 6500,
    spoiler_carbon: 1200,
    wrap_autocolant: 3500,
    underglow: 400,
    scaune_scoica: 2800,
    volan_sport: 900,
    nitro_kit: 5000, // Bonus de la Vericu
  },
  branduri: {
    BMW: {
      amp: 2.5,
      modele: {
        "E46 (Cazan)": 1.1,
        E90: 1.3,
        F30: 1.6,
        M5: 2.5,
        "Seria 7": 2.2,
        X5: 1.9,
      },
    },
    Audi: {
      amp: 2.3,
      modele: {
        A3: 1.2,
        "A4 B8": 1.4,
        "A6 Matrix": 1.8,
        "A8 Sport": 2.3,
        Q7: 2.0,
        "R8 (Dacă ai bani)": 3.5,
      },
    },
    Mercedes: {
      amp: 2.8,
      modele: {
        "C-Class": 1.4,
        "E-Class": 1.7,
        "S-Class (Șefie)": 2.5,
        "G-Wagon": 3.0,
        GLE: 2.1,
        Vito: 1.2,
      },
    },
    Volkswagen: {
      amp: 1.2,
      modele: {
        "Golf 4 (Legendă)": 0.9,
        "Golf 7": 1.3,
        "Passat B6 (Piele)": 1.2,
        "Passat B8": 1.5,
        Tiguan: 1.6,
        Touareg: 1.9,
      },
    },
    Opel: {
      amp: 0.7,
      modele: {
        "Astra G": 0.9,
        "Astra J": 1.2,
        Insignia: 1.4,
        Corsa: 0.8,
        Zafira: 1.1,
        "Vectra B": 0.8,
      },
    },
    Dacia: {
      amp: 0.5,
      modele: {
        "Logan 1": 0.7,
        "Logan 3": 1.1,
        "Sandero Stepway": 1.0,
        "Duster 4x4": 1.3,
        "Spring (Drujbă)": 1.5,
        "1310 (Clasic)": 0.6,
      },
    },
    Ford: {
      amp: 1.0,
      modele: {
        "Focus 2": 1.0,
        "Focus 4": 1.3,
        Mondeo: 1.4,
        Fiesta: 0.9,
        Kuga: 1.5,
        Mustang: 2.2,
      },
    },
    Renault: {
      amp: 0.9,
      modele: {
        Clio: 0.9,
        "Megane 3": 1.1,
        "Megane 4": 1.3,
        "Laguna (Problematică)": 1.4,
        Kadjar: 1.4,
        Zoe: 1.6,
      },
    },
    Toyota: {
      amp: 1.5,
      modele: {
        Corolla: 1.2,
        Avensis: 1.3,
        RAV4: 1.6,
        "Land Cruiser": 2.4,
        Hilux: 1.8,
        Supra: 2.8,
      },
    },
    Skoda: {
      amp: 1.1,
      modele: {
        "Octavia 2": 1.1,
        "Octavia 4": 1.4,
        Superb: 1.6,
        Fabia: 0.9,
        Kodiaq: 1.7,
        Karoq: 1.5,
      },
    },
    Hyundai: {
      amp: 1.1,
      modele: {
        i20: 0.9,
        i30: 1.1,
        Tucson: 1.5,
        "Santa Fe": 1.7,
        Elantra: 1.2,
        "Ioniq 5": 1.9,
      },
    },
    Porsche: {
      amp: 4.5,
      modele: {
        "911 Carrera": 3.0,
        Cayenne: 2.5,
        Panamera: 2.8,
        Macan: 2.2,
        Taycan: 3.5,
      },
    },
    Tesla: {
      amp: 3.5,
      modele: {
        "Model 3": 1.8,
        "Model S": 2.2,
        "Model X": 2.5,
        "Model Y": 1.9,
        Cybertruck: 4.0,
      },
    },
  },
  tuninguri: [
    {
      id: "ulei",
      categorie: "Revizie Motor",
      optiuni: [
        {
          id: "ulei_vericu",
          nume: "Ulei de la Vericu",
          mesaj: "Unge motorul mai bine ca vaselina!",
          ore: 1,
          piese: [
            { id: "ulei_bidon", cant: 1 },
            { id: "saiba_cupru", cant: 1 },
            { id: "sarma_otel", cant: 2 },
          ],
        },
        {
          id: "ulei_special",
          nume: "Ulei Racing 0W-99",
          mesaj: "Să nu se prăjească pistoanele la 9000 RPM!",
          ore: 1.5,
          piese: [
            { id: "ulei_racing", cant: 1 },
            { id: "saiba_cupru", cant: 2 },
            { id: "filtru_ulei", cant: 1 },
          ],
        },
      ],
    },
    {
      id: "soft",
      categorie: "ECU Remap (Soft)",
      optiuni: [
        {
          id: "st1",
          nume: "Stage 1 ECU",
          mesaj: "Scoatem untul din ea fără să rupem nimic.",
          ore: 2,
          piese: [{ id: "soft_st1", cant: 1 }],
        },
        {
          id: "st2",
          nume: "Stage 2 ECU",
          mesaj: "Deja începe să fluiere a pagubă.",
          ore: 4,
          piese: [{ id: "soft_st2", cant: 1 }],
          cereObligatoriu: {
            categorie: "evacuare",
            optiuneId: "downpipe_sport",
          },
          msgBlocare:
            "Vericu: Nu facem Stage 2 cu evacuare de fabrică, se sufocă!",
        },
        {
          id: "st3",
          nume: "Stage 3 (Rachetă)",
          mesaj: "Adio garanție, bun venit adrenalină!",
          ore: 8,
          piese: [
            { id: "soft_st3", cant: 1 },
            { id: "launch_control", cant: 1 },
          ],
          cereObligatoriu: { categorie: "turbo", optiuneId: "turbina_st3" },
          msgBlocare: "Vericu: Stage 3 fără turbină mare? Ești optimist, boss!",
        },
      ],
    },
    {
      id: "evacuare",
      categorie: "Sistem Evacuare",
      optiuni: [
        {
          id: "downpipe_sport",
          nume: "Downpipe Sport",
          mesaj: "Să respire și motorul tău un pic.",
          ore: 3,
          piese: [{ id: "downpipe", cant: 1 }],
        },
        {
          id: "full_exhaust",
          nume: "Full Sport Exhaust",
          mesaj: "Să te audă vecinii când pleci la muncă!",
          ore: 6,
          piese: [
            { id: "evacuare_full", cant: 1 },
            { id: "catalizator_sport", cant: 1 },
          ],
        },
        {
          id: "decat",
          nume: "Decat Pipe",
          mesaj: "Vericu zice: Cine are nevoie de mediu când ai cai?",
          ore: 2,
          piese: [{ id: "teava_decat", cant: 1 }],
        },
      ],
    },
    {
      id: "turbo",
      categorie: "Inducție Forțată",
      optiuni: [
        {
          id: "turbina_st3",
          nume: "Turbină Garrett",
          mesaj: "De aici ai nevoie de parașută, nu frâne!",
          ore: 12,
          piese: [
            { id: "turbina_avion", cant: 1 },
            { id: "prezon_otel", cant: 4 },
            { id: "garnitura_foc", cant: 1 },
          ],
          cereObligatoriu: { categorie: "ulei", optiuneId: "ulei_special" },
          msgBlocare:
            "Vericu: Turbina asta prăjește uleiul de floarea soarelui!",
        },
        {
          id: "twin_turbo",
          nume: "Twin Turbo Setup",
          mesaj: "Două e mai bune ca una, zice Vericu!",
          ore: 20,
          piese: [
            { id: "twin_turbo", cant: 1 },
            { id: "intercooler_mare", cant: 1 },
          ],
        },
        {
          id: "supercharger",
          nume: "Supercharger Kit",
          mesaj: "Putere instantă, fără lag, direct pe pedală!",
          ore: 16,
          piese: [{ id: "supercharger", cant: 1 }],
        },
      ],
    },
    {
      id: "transmisie",
      categorie: "Transmisie & Ambreiaj",
      optiuni: [
        {
          id: "clutch_perf",
          nume: "Ambreiaj Performance",
          mesaj: "Să nu mai patineze când îi dai talpă.",
          ore: 8,
          piese: [
            { id: "ambreiaj_perfor", cant: 1 },
            { id: "volanta_masa_simpla", cant: 1 },
          ],
        },
        {
          id: "shifter",
          nume: "Short Shifter",
          mesaj: "Schimbi vitezele mai repede ca Vericu la table.",
          ore: 2,
          piese: [{ id: "short_shifter", cant: 1 }],
        },
      ],
    },
    {
      id: "suspensie",
      categorie: "Suspensie & Handling",
      optiuni: [
        {
          id: "coilovers",
          nume: "Coilovers Reglabile",
          mesaj: "O lăsăm pe burtă să nu treacă nici furnica!",
          ore: 5,
          piese: [
            { id: "coilover_set", cant: 1 },
            { id: "bucse_poliuretan", cant: 4 },
          ],
        },
        {
          id: "air_ride",
          nume: "Suspensie pe Aer",
          mesaj: "Ți-o ridici când vezi bordura, boss!",
          ore: 12,
          piese: [{ id: "perne_aer", cant: 1 }],
        },
      ],
    },
    {
      id: "franare",
      categorie: "Sistem Frânare",
      optiuni: [
        {
          id: "big_brakes",
          nume: "Big Brake Kit",
          mesaj: "Te oprești înainte să te gândești.",
          ore: 4,
          piese: [
            { id: "big_brake_kit", cant: 1 },
            { id: "brake_pads", cant: 2 },
          ],
        },
      ],
    },
    {
      id: "estetica",
      categorie: "Aspect Exterior",
      optiuni: [
        {
          id: "widebody",
          nume: "Widebody Kit",
          mesaj: "Mai lat ca tiru!",
          ore: 30,
          piese: [
            { id: "widebody_kit", cant: 1 },
            { id: "jante_aliaj", cant: 1 },
            { id: "spacers", cant: 4 },
          ],
        },
        {
          id: "wrap",
          nume: "Wrap Full Color",
          mesaj: "Schimbăm culoarea ca pe șosete.",
          ore: 15,
          piese: [{ id: "wrap_autocolant", cant: 1 }],
        },
        {
          id: "pachet_lumini",
          nume: "Underglow & Ambient",
          mesaj: "Fast & Furious, varianta de cartier.",
          ore: 4,
          piese: [{ id: "underglow", cant: 1 }],
        },
      ],
    },
    {
      id: "special",
      categorie: "Nebunii de-ale lui Vericu",
      optiuni: [
        {
          id: "nitro",
          nume: "Sistem Nitro (NOS)",
          mesaj: "Dă-i butonul ăla și zboară, puiule!",
          ore: 10,
          piese: [{ id: "nitro_kit", cant: 1 }],
          cereObligatoriu: {
            categorie: "transmisie",
            optiuneId: "clutch_perf",
          },
          msgBlocare: "Vericu: Nitro fără ambreiaj? Îți lasă cutia în urmă!",
        },
      ],
    },
  ],
};

function init() {
  const brandSel = document.getElementById("brand-select");
  const modelSel = document.getElementById("model-select");
  const calcGrid = document.getElementById("calculator-grid");

  // Populate Brands
  Object.keys(DB.branduri).forEach((b) => {
    brandSel.innerHTML += `<option value="${b}">${b}</option>`;
  });

  // Handle Model change on Brand selection
  brandSel.addEventListener("change", () => {
    const brand = DB.branduri[brandSel.value];
    modelSel.innerHTML = "";
    Object.keys(brand.modele).forEach((m) => {
      modelSel.innerHTML += `<option value="${brand.modele[m]}">${m}</option>`;
    });
    actualizeaza();
  });

  // Populate Tuning Cards
  DB.tuninguri.forEach((t) => {
    let card = document.createElement("div");
    card.className = "option-card";
    card.innerHTML = `
            <h3>${t.categorie}</h3>
            <select class="tuning-select" data-cat-id="${t.id}" onchange="actualizeaza()">
                <option value="none">-- Nimic --</option>
                ${t.optiuni.map((o) => `<option value="${o.id}">${o.nume}</option>`).join("")}
            </select>
            <p class="vericu-msg" id="msg-${t.id}"></p>
        `;
    calcGrid.appendChild(card);
  });

  brandSel.dispatchEvent(new Event("change"));
}

function actualizeaza() {
  const selectedBrand = document.getElementById("brand-select").value;
  const modelAmp = parseFloat(document.getElementById("model-select").value);
  const brandAmp = DB.branduri[selectedBrand].amp;
  const anInput = parseInt(document.getElementById("an-input").value) || 2010;

  // 1. RESETARE
  document.querySelectorAll(".tuning-select").forEach((sel) => {
    sel.disabled = false;
    sel.parentElement.classList.remove("forced");
    const msgId = `msg-${sel.dataset.catId}`;
    if (document.getElementById(msgId))
      document.getElementById(msgId).innerText = "";
  });

  const distantaAn = Math.abs(anInput - DB.settings.anEpicentru);
  const ampAn = 1 + distantaAn * DB.settings.factorAn;

  const invoiceBody = document.getElementById("invoice-body");
  invoiceBody.innerHTML = "";

  let subtotalGeneral = 0;
  const selections = {};

  document.querySelectorAll(".tuning-select").forEach((sel) => {
    selections[sel.dataset.catId] = sel.value;
  });

  // 2. LOGICA DEPENDENȚE
  DB.tuninguri.forEach((t) => {
    t.optiuni.forEach((o) => {
      if (selections[t.id] === o.id && o.cereObligatoriu) {
        const targetCat = o.cereObligatoriu.categorie;
        const targetOpt = o.cereObligatoriu.optiuneId;
        const targetSelect = document.querySelector(
          `[data-cat-id="${targetCat}"]`,
        );
        if (targetSelect) {
          targetSelect.value = targetOpt;
          targetSelect.disabled = true;
          targetSelect.parentElement.classList.add("forced");
          const msgEl = document.getElementById(`msg-${targetCat}`);
          if (msgEl) msgEl.innerText = o.msgBlocare;
          selections[targetCat] = targetOpt;
        }
      }
    });
  });

  // 3. CALCUL FINAL ȘI GENERARE TABEL
  DB.tuninguri.forEach((t) => {
    const select = document.querySelector(`[data-cat-id="${t.id}"]`);
    const val = selections[t.id];
    const msgPara = document.getElementById(`msg-${t.id}`);

    if (val !== "none") {
      const opt = t.optiuni.find((o) => o.id === val);
      if (msgPara && !select.disabled) msgPara.innerText = opt.mesaj;

      // --- CALCUL PIESE: AICI E SOLUȚIA ---
      let costPieseRunda = 0; // Suma pieselor deja rotunjite
      const detaliiPiese = opt.piese
        .map((p) => {
          const pretUnitatAjustat =
            DB.piese_globale[p.id] * brandAmp * modelAmp * ampAn;
          const pretTotalPiesaFloat = pretUnitatAjustat * p.cant;
          const pretPiesaRotunjit = Math.round(pretTotalPiesaFloat);

          // Adunăm valoarea deja rotunjită ca să nu pierdem lei pe drum
          costPieseRunda += pretPiesaRotunjit;

          return `${p.id.replace("_", " ")} (x${p.cant}: ${pretPiesaRotunjit} lei)`;
        })
        .join(", ");

      // --- CALCUL MANOPERĂ ---
      const oreMunca = opt.ore || 1;
      const costManoperaFinal = Math.round(
        oreMunca * DB.settings.tarifOrarBaza * brandAmp * modelAmp * ampAn,
      );

      // Totalul rândului folosind piesele deja rotunjite
      const totalRandFinal = costPieseRunda + costManoperaFinal;
      subtotalGeneral += totalRandFinal;

      invoiceBody.innerHTML += `
        <tr>
            <td>
                <strong>${opt.nume}</strong><br>
                <small style="color: #666;">Piese: ${detaliiPiese}</small>
            </td>
            <td><i>"${opt.mesaj}"</i></td>
            <td>${costPieseRunda} lei</td>
            <td>${costManoperaFinal} lei (${oreMunca}h)</td>
            <td><strong>${totalRandFinal} lei</strong></td>
        </tr>`;
    } else {
      if (msgPara) msgPara.innerText = "";
    }
  });

  // 4. CALCUL TAXE ȘI TOTAL FINAL
  const tva = Math.round(subtotalGeneral * DB.settings.tva);
  const totalFinal = subtotalGeneral + tva;

  document.getElementById("subtotal").innerText = subtotalGeneral;
  document.getElementById("tva-val").innerText = tva;
  document.getElementById("grand-total-val").innerText = totalFinal;
}

document.addEventListener("DOMContentLoaded", init);

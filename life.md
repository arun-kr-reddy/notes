- [personal finance](#personal-finance)
- [ESOPs tax filing](#esops-tax-filing)
- [upskilling](#upskilling)
- [quotes](#quotes)

# links  <!-- omit from toc -->
- [resume tips](https://www.reddit.com/r/developersIndia/comments/1b401so/few_tips_to_get_your_naukri_resume_shortlisted_by/)

# personal finance
- **why save money:** future is unknown territory (like AI taking over jobs) so best to save for future  
  would be relieving to know you don't have to work and could walk away from your job if you wanted  
  think about you being old being unable to work to earn and needing money
- **hedonic treadmill:** people quickly adapt to positive changes leading to return to neutral happiness  
  positive events initially boost happiness but the effect is often temporary  
  ![](./media/life/hedonic_treadmill.png)
- **why sell ESOPs on vest:** hold only if you would buy your company stock if you had cash  
  stock falling in future and losing your job correlated  
  unvested stocks and salary increases already give exposure to company's growth
- **why not track every rupee:** waste of time once you've got your impulses under control  
  you are on track as long as you hit your savings goal, energy should be spent on making money and keeping yourself healthy & happy
- **why stay back in india:** europe needs skilled immigrants to fund their ponzi scheme of social welfare  
  wait times for anything beyond a cold varies from several weeks to few months  
  all the tech companies in india have good total compensation & big teams with decent work now

# [ESOPs tax filing](https://www.youtube.com/watch?v=NO6OlUI1Hz4)
- [sample spreadsheet](https://docs.google.com/spreadsheets/d/1oIXQBw2UPs85bPaDNYrtJTxoSkKj0gQ7glok59ZK_Gs/edit?usp=sharing) (use [SBI TT rate](https://github.com/sahilgupta/sbi-fx-ratekeeper/blob/main/csv_files/SBI_REFERENCE_RATES_USD.csv) for INR ⟷ USD)
- form12B has total RSU & ESPP already-taxed income  
  individual amount in tax-computation-sheet
- **ESPP:** `num_shares * (purchase_date_FMV - purchase_price)` already taxed  
  so only need to compute profit (using [gain & losses](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses)) `num_shares * (sale_price - purchase_date_FMV)`  
  ![](./media/life/esop_taxation_espp.png)
- **RSUs:** `num_shares * vest_date_FMV` already taxed  
  so only need to compute profit (using [gain & losses](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses)) `num_shares * (sale_price - vest_date_FMV)`  
  **note:** one-third shares sold on vesting, so figure out order pairs of auto-covered-sale and what-you-sold  
  ![](./media/life/esop_taxation_rsu.png)
- **1042S:** dividends are taxed by US at 25% which can be used as tax credits using [1042S](https://us.etrade.com/etx/pxy/tax-center)  
  use these by converting to INR and filling [form67](https://eportal.incometax.gov.in/iec/foservices/#/dashboard/fileIncomeTaxForm)
- **ITR schedules:**
  - **capital gains:** fill combined purchase & sale price  
    add dividend as other sources
  - **foreign source income (FSI):** fill RSUs & ESPP gain
  - **foreign assets (FA):** fill combined purchase & sale price for calendar year

# upskilling
- **3 months growth:** time to hope over to the next company/team if you can't update a single thing in your resume
- [**DSA prep:**](https://www.reddit.com/r/cscareerquestions/comments/ot9ssf/comment/h6tx1vx/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button)
  - start timing yourself after first week of leetcode
  - stop timer and mark problem as failed if you have to google something when totally stuck
  - goal is to understand the problem and not memorize solution  
    so give yourself time to forget before returning to failed problems
  - if you can't solve new problems then you are memorizing solutions
  - get into leetcode shape by learning the strategies   
    getting back into it again later will just take weeks

# quotes
- *advertising has us chasing cars & clothes, working jobs we hate so we can buy shit we don't need*
- *just because you can afford it doesn't mean you should buy it*
- *AI can only replace you if your work is already done and readily accessible over the internet, AI cannot replace novelty*
- *code is read more than it is written, so code clarity trumps micro-optimization*
- *nothing more permanent than a temporary fix that works*